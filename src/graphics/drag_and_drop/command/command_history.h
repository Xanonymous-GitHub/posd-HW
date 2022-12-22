#pragma once

#include "command.h"
#include "macro_command.h"
#include <stack>
#include <stdexcept>
#include <vector>

class CommandHistory {
private:
    bool inMacro = false;
    std::stack<Command *> _history;
    std::stack<Command *> _undoCommands;

    template <typename T>
    void safeCleanStackOf_(std::stack<T *> &s) {
        while (!s.empty()) {
            delete s.top();
            s.pop();
        }
    }

public:
    CommandHistory() = default;

    ~CommandHistory() {
        safeCleanStackOf_(_history);
        safeCleanStackOf_(_undoCommands);
    }

    void beginMacroCommand() {
        if (inMacro) {
            return;
        }

        inMacro = true;

        const auto newMacroCmd = new MacroCommand{};
        _history.push(newMacroCmd);
    }

    void addCommand(Command *const command) {
        if (command == nullptr) {
            throw AddingNullCommandException{"adding a null command into macro command!"};
        }

        if (inMacro) {
            _history.top()->addCommand(command);
        } else {
            _history.push(command);
        }
    }

    void endMacroCommand() {
        if (!inMacro) {
            return;
        }

        inMacro = false;
    }

    void undo() {
        if (_history.empty()) {
            return;
        }

        const auto cmd = _history.top();
        cmd->undo();
        _history.pop();
        _undoCommands.push(cmd);
    }

    std::stack<Command *> getHistory() const {
        return _history;
    }

    class AddingNullCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};