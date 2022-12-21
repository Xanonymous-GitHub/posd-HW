#pragma once

#include "command.h"
#include <iterator>
#include <stdexcept>
#include <vector>

class MacroCommand : public Command {
private:
    std::vector<Command *> _commands;

public:
    MacroCommand() = default;

    ~MacroCommand() {
        for (auto &&it : _commands) {
            if (it != nullptr) {
                delete it;
                it = nullptr;
            }
        }

        _commands.clear();
    }

    void execute() override {
        for (auto &&it : _commands) {
            if (it == nullptr) {
                throw FailedToExecuteCommandException{"could not exec a null command!"};
            }

            it->execute();
        }
    }

    void addCommand(Command *const command) override {
        if (command == nullptr) {
            throw AddingNullCommandException{"adding a null command into macro command!"};
        }

        _commands.push_back(command);
    }

    void undo() override {
        /**
         * @brief Reverse view of a sequence container (only C++20 or above)
         *
         * @example
         * #include <ranges>
         * using namespace ranges;
         * for (auto &&it : _commands | views::reverse) { ... }
         */

        for (auto &&it = _commands.crbegin(); it != _commands.crend(); it++) {
            if (*it == nullptr) {
                throw FailedToUndoCommandException{"could not undo a null command!"};
            }

            (*it)->undo();
        }
    }

    std::vector<Command *> getCommands() const override {
        return _commands;
    }

    class AddingNullCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
