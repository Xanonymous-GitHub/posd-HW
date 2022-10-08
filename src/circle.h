#pragma once

#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <cmath>
#include <string>

class Circle : public Shape {
private:
    const TwoDimensionalVector *const _radiusVec;
    const std::string name_ = "Circle";

public:
    Circle(const TwoDimensionalVector *const radiusVec) : _radiusVec(radiusVec) {}

    ~Circle() {
        // Ownership of the radius vector is not transferred to the circle.
        // Therefore, the circle does not delete the radius vector.
    }

    double radius() const {
        return _radiusVec->length();
    }

    double area() const override {
        return M_PI * radius() * radius();
    }

    double perimeter() const override {
        return 2 * M_PI * radius();
    }

    std::string info() const override {
        return "Circle (" + _radiusVec->info() + ")";
    }

    std::string name() const override {
        return name_;
    }

    Iterator *createDFSIterator() const override {
        return new NullIterator();
    }

    Iterator *createBFSIterator() const override {
        return new NullIterator();
    }
};