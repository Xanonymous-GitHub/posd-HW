#pragma once

#include "../drag_and_drop.h"
#include "../mouse_position.h"
#include "command.h"
#include "command_history.h"

class DropCommand : public Command {
private:
    DragAndDrop *_dragAndDrop = nullptr;
    CommandHistory *_commandHistory = nullptr;
    double _x, _y;

    bool isValidCouplingExist_() const {
        return _dragAndDrop != nullptr && _commandHistory != nullptr;
    }

    void updateCurrentXY() {
        const auto xy = currentXY_();
        _x = xy.first;
        _y = xy.second;
    }

public:
    DropCommand(
        DragAndDrop *const dragAndDrop,
        CommandHistory *const commandHistory) : _dragAndDrop{dragAndDrop},
                                                _commandHistory{commandHistory} {}

    DropCommand(const DropCommand &dropCommand) = default;

    DropCommand(DropCommand &&c) = default;

    void execute() override {
        if (!isValidCouplingExist_()) {
            throw FailedToExecuteCommandException{"Failed to exec command!"};
        }

        updateCurrentXY();

        _dragAndDrop->drop(_x, _y);
        _commandHistory->addCommand(new DropCommand{*this});
    }

    void undo() override {
        if (!isValidCouplingExist_()) {
            throw FailedToUndoCommandException{"Failed to undo command!"};
        }

        _commandHistory->undo();
    }

    double getX() const noexcept {
        return _x;
    }

    double getY() const noexcept {
        return _y;
    }
};
