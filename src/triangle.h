#pragma once

#include "shape.h"
#include "two_dimensional_vector.h"
#include <string>

class Triangle : public Shape {
private:
    const TwoDimensionalVector *_v1;
    const TwoDimensionalVector *_v2;

public:
    Triangle(
        const TwoDimensionalVector *v1,
        const TwoDimensionalVector *v2) : _v1(v1), _v2(v2) {}

    ~Triangle() {}

    const double area() const override {}

    const double perimeter() const override {}

    const std::string info() const override {}
};