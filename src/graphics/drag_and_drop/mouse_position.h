#pragma once

#include <stdexcept>

class MousePosition {
private:
    double _x, _y;

protected:
    MousePosition() = default;

public:
    ~MousePosition() = default;

    static MousePosition *getInstance() {
        static MousePosition _instance;
        return &_instance;
    }

    void setPos(const double &x, const double &y) {
        _x = x;
        _y = y;
    }

    double getX() const noexcept {
        return _x;
    }

    double getY() const noexcept {
        return _y;
    }

    class InstanceNotFoundException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
