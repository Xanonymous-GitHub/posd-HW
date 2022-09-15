#pragma once

#include "shape.h"
#include "two_dimensional_vector.h"
#include <cmath>
#include <string>

class Circle : public Shape {
private:
    const TwoDimensionalVector *_radiusVec;

public:
    Circle(const TwoDimensionalVector *radiusVec) : _radiusVec(radiusVec) {}

    ~Circle() {
        // Ownership of the radius vector is not transferred to the circle.
        // Therefore, the circle does not delete the radius vector.
    }

    const double radius() const {
        return _radiusVec->length();
    }

    const double area() const override {
        return M_PI * radius() * radius();
    }

    const double perimeter() const override {
        return 2 * M_PI * radius();
    }

    const std::string info() const override {
        return "Circle (" + _radiusVec->info() + ")";
    }
};