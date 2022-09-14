#pragma once

#include <string>
#include <cmath>
#include "two_dimensional_vector.h"
#include "shape.h"

class Circle : public Shape {
private:
    TwoDimensionalVector *_radiusVec;

public:
    Circle(TwoDimensionalVector *radiusVec) {}

    ~Circle() {}

    double radius() const {}

    double area() const override {}

    double perimeter() const override {}

    std::string info() const override {}
};