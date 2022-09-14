#pragma once

#include <string>
#include "shape.h"
#include "two_dimensional_vector.h"

class Rectangle : public Shape {
private:
    TwoDimensionalVector *_lengthVec;
    TwoDimensionalVector *_widthVec;

public:
    Rectangle(TwoDimensionalVector *lengthVec, TwoDimensionalVector *widthVec) {}

    ~Rectangle() {}

    double length() const {}

    double width() const {}

    double area() const override {}

    double perimeter() const override {}

    std::string info() const override {}
};