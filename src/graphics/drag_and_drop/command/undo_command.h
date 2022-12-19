#pragma once

#include "../drag_and_drop.h"
#include "command.h"
#include "command_history.h"

class UndoCommand : public Command {
private:
    CommandHistory *_commandHistory = nullptr;

    bool isValidCouplingExist_() const {
        return _commandHistory != nullptr;
    }

public:
    UndoCommand(
        DragAndDrop *const dragAndDrop,
        CommandHistory *const commandHistory) : _commandHistory{commandHistory} {}

    void execute() override {
        if (!isValidCouplingExist_()) {
            throw FailedToUndoCommandException{"Failed to undo command!"};
        }

        _commandHistory->undo();
    }

    void undo() override{};
};
