#pragma once

#include <string>
#include "shape.h"
#include "two_dimensional_vector.h"

class Triangle : public Shape {
private:
    TwoDimensionalVector *_v1;
    TwoDimensionalVector *_v2;

public:
    Triangle(TwoDimensionalVector *v1, TwoDimensionalVector *v2) {}

    ~Triangle() {}

    double area() const override {}

    double perimeter() const override {}

    std::string info() const override {}
};