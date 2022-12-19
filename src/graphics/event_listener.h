#pragma once

#include "./drag_and_drop/command/command.h"
#include "./drag_and_drop/drag_and_drop.h"
#include "./drag_and_drop/mouse_position.h"
#include <memory>
#include <unordered_map>

class EventListener {
private:
    std::unordered_map<std::string, std::unique_ptr<Command>> _callbacks;

    void _trigger(const std::string &eventName, const double &x, const double &y) const {
        MousePosition::getInstance()->setPos(x, y);

        if (_callbacks.find(eventName) != _callbacks.cend()) {
            _callbacks.at(eventName)->execute();
        } else {
            std::cout << "Event: " << eventName << "is not registered." << std::endl;
        }
    }

public:
    void leftMouseMove(const double &x, const double &y) const {
        _trigger("Left_Mouse_Move", x, y);
    }

    void leftMouseDown(const double &x, const double &y) const {
        _trigger("Left_Mouse_Down", x, y);
    }

    void rightMouseDown(const double &x, const double &y) const {
        _trigger("Right_Mouse_Down", x, y);
    }

    void leftMouseUp(const double &x, const double &y) const {
        _trigger("Left_Mouse_Up", x, y);
    }

    void refresh(const double &x, const double &y) const {
        _trigger("Refresh", x, y);
    }

    void on(const std::string &eventName, Command *const callback) {
        _callbacks.at(eventName) = std::unique_ptr<Command>(callback);
    }
};
