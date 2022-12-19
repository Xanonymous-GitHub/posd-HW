#pragma once

#include "command.h"
#include "macro_command.h"
#include <stack>

class CommandHistory {
private:
    bool inMacro = false;
    std::stack<Command *> _history;
    std::stack<Command *> _undoCommands;

public:
    CommandHistory() {}

    ~CommandHistory() {}

    void beginMacroCommand() {}

    void addCommand(Command *const command) {}

    void endMacroCommand() {}

    void undo() {}

    std::stack<Command *> getHistory() const {}
};