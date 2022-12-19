#pragma once

#include "../drag_and_drop.h"
#include "command.h"
#include "command_history.h"

class UndoCommand : public Command {

private:
    DragAndDrop *_dragAndDrop;
    CommandHistory *_commandHistory;

public:
    UndoCommand(
        DragAndDrop *const dragAndDrop,
        CommandHistory *const commandHistory) : _dragAndDrop{dragAndDrop},
                                                _commandHistory{commandHistory} {}

    void execute() override {}

    void undo() override {}
};
