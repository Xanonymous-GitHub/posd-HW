#pragma once

#include "../drag_and_drop.h"
#include "../mouse_position.h"
#include "command.h"
#include "command_history.h"

class DropCommand : public Command {
private:
    DragAndDrop *_dragAndDrop;
    CommandHistory *_commandHistory;
    double _x, _y;

public:
    DropCommand(
        DragAndDrop *const dragAndDrop,
        CommandHistory *const commandHistory) : _dragAndDrop{dragAndDrop},
                                                _commandHistory{commandHistory} {}

    DropCommand(const DropCommand &dropCommand) = default;

    DropCommand(DropCommand &&c) = default;

    void execute() override {}

    void undo() override {}

    double getX() const {}

    double getY() const {}
};