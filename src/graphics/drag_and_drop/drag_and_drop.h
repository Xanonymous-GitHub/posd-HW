#pragma once

#include "../../circle.h"
#include "../../compound_shape.h"
#include "../../shape.h"
#include "../../two_dimensional_vector.h"
#include "../../visitor/collision_detector.h"
#include <iostream>
#include <vector>

class DragAndDrop {
private:
    std::vector<Shape *> _shapes;
    Shape *_target_shape = nullptr;
    double _previousX, _previousY;

public:
    DragAndDrop() = default;
    DragAndDrop(const std::vector<Shape *> &shapes) : _shapes{shapes} {}
    ~DragAndDrop() = default;

    virtual void grab(double x, double y) {
        const Point c1{x, y}, c2{x, y};
        const TwoDimensionalVector mr{c1, c2};
        const Circle mousePoint{mr};
        CollisionDetector cd{&mousePoint};

        for (auto &&it : _shapes) {
            it->accept(&cd);
        }

        const auto selectedShapes = cd.collidedShapes();

        if (selectedShapes.size() > 0) {
            _target_shape = cd.collidedShapes()[0];
        }

        _previousX = x;
        _previousY = y;
    }

    virtual void move(double x, double y) {
        if (_target_shape != nullptr) {
            const double deltaX = x - _previousX, deltaY = y - _previousY;
            _target_shape->move(deltaX, deltaY);
            _previousX = x;
            _previousY = y;
        } else {
            std::cout << "The target shape is not specified yet." << std::endl;
        }
    }

    virtual void drop(double x, double y) {
        _target_shape = nullptr;
    }
};
