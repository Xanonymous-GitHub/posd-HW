#pragma once

#include "shape.h"
#include "two_dimensional_vector.h"
#include <string>

class Rectangle : public Shape {
private:
    const TwoDimensionalVector *_lengthVec;
    const TwoDimensionalVector *_widthVec;

public:
    Rectangle(
        const TwoDimensionalVector *lengthVec,
        const TwoDimensionalVector *widthVec) : _lengthVec(lengthVec), _widthVec(widthVec) {}

    ~Rectangle() {}

    const double length() const {}

    const double width() const {}

    const double area() const override {}

    const double perimeter() const override {}

    const std::string info() const override {}
};