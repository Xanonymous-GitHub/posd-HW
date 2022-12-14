#pragma once

#include "../drag_and_drop.h"
#include "../mouse_position.h"
#include "command.h"
#include "command_history.h"

class GrabCommand : public Command {
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
    GrabCommand(
        DragAndDrop *const dragAndDrop,
        CommandHistory *const commandHistory) : _dragAndDrop{dragAndDrop},
                                                _commandHistory{commandHistory} {}

    GrabCommand(const GrabCommand &grabCommand) = default;

    void execute() override {
        if (!isValidCouplingExist_()) {
            throw FailedToExecuteCommandException{"Failed to exec command!"};
        }

        updateCurrentXY();

        _dragAndDrop->grab(_x, _y);
        _commandHistory->beginMacroCommand();
        _commandHistory->addCommand(new GrabCommand{*this});
    }

    void undo() override {
        if (!isValidCouplingExist_()) {
            throw FailedToUndoCommandException{"Failed to undo command!"};
        }

        _dragAndDrop->move(_x, _y);
        _dragAndDrop->drop(_x, _y);
    }

    double getX() const noexcept {
        return _x;
    }

    double getY() const noexcept {
        return _y;
    }
};
