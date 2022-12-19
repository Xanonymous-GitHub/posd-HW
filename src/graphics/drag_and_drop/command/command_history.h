#pragma once

#include "command.h"
#include "macro_command.h"
#include <stack>
#include <stdexcept>

class CommandHistory {
private:
    bool inMacro = false;
    std::stack<Command *> _history;
    std::stack<Command *> _undoCommands;

public:
    CommandHistory() {}

    ~CommandHistory() {}

    void beginMacroCommand() {}

    void addCommand(Command *const command) {
        if (command == nullptr) {
            throw AddingNullCommandException{"adding a null command into macro command!"};
        }

        // TODO: wrap inside macro command.
        _history.push(command);
    }

    void endMacroCommand() {}

    void undo() {}

    std::stack<Command *> getHistory() const {
        return _history;
    }

    class AddingNullCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};