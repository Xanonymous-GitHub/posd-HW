#pragma once

#include "../mouse_position.h"
#include <stdexcept>
#include <utility>

class Command {
protected:
    std::pair<double, double> currentXY_() const {
        const auto mousePosition = MousePosition::getInstance();
        if (mousePosition == nullptr) {
            throw MousePosition::InstanceNotFoundException{"mousePosition is null"};
        }

        const auto &&x = mousePosition->getX();
        const auto &&y = mousePosition->getY();
        return std::make_pair(x, y);
    }

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

    class FailedToExecuteCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    class FailedToUndoCommandException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
