#pragma once

#include "../drag_and_drop.h"
#include "../mouse_position.h"
#include "command.h"
#include "command_history.h"

class MoveCommand : public Command {
private:
    DragAndDrop *_dragAndDrop = nullptr;
    CommandHistory *_commandHistory = nullptr;
    double _x, _y;

public:
    MoveCommand(
        DragAndDrop *const dragAndDrop,
        CommandHistory *const commandHistory) : _dragAndDrop{dragAndDrop},
                                                _commandHistory{commandHistory} {}

    MoveCommand(const MoveCommand &moveCommand) = default;

    void execute() override {}

    void undo() override {}

    double getX() const {}

    double getY() const {}
};
