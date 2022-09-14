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

    ~Circle() {}

    const double radius() const {}

    const double area() const override {}

    const double perimeter() const override {}

    const std::string info() const override {}
};