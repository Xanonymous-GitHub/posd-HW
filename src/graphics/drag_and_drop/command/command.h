#pragma once

#include <stdexcept>

class Command {
public:
    virtual ~Command() = default;

    virtual void execute() = 0;

    virtual void undo() = 0;

    virtual void addCommand(Command *const command) {
        throw FailedToAddCommandException{"cannot add command."};
    }

    virtual std::vector<Command *> getCommands() const {
        throw FailedToGetCommandException{"cannot get commands."};
    }

    class FailedToAddCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class FailedToGetCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
