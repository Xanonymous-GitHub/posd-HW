#pragma once

#include "../../../src/graphics/drag_and_drop/drag_and_drop.h"

class MockDragAndDrop : public DragAndDrop {
private:
    double _grabX = 0, _grabY = 0;
    double _moveX = 0, _moveY = 0;
    double _dropX = 0, _dropY = 0;

public:
    void grab(double x, double y) override {
        _grabX = x;
        _grabY = y;
    }

    void move(double x, double y) override {
        _moveX = x;
        _moveY = y;
    }

    void drop(double x, double y) override {
        _dropX = x;
        _dropY = y;
    }

    double getGrabX() const {
        return _grabX;
    }
    double getMoveX() const {
        return _moveX;
    }
    double getDropX() const {
        return _dropX;
    }
    double getGrabY() const {
        return _grabY;
    }
    double getMoveY() const {
        return _moveY;
    }
    double getDropY() const {
        return _dropY;
    }
};