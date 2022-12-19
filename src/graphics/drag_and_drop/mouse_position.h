#pragma once

class MousePosition {
private:
    MousePosition() = default;

    static MousePosition *_instance;
    double _x, _y;

public:
    ~MousePosition() {}

    static MousePosition *getInstance() {
        if (_instance == nullptr) {
            _instance = new MousePosition();
        }
        return _instance;
    }

    void setPos(const double &x, const double &y) {
        _x = x;
        _y = y;
    }

    double getX() noexcept {
        return _x;
    }

    double getY() noexcept {
        return _y;
    }
};

MousePosition *MousePosition::_instance;
