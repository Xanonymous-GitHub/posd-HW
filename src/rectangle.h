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

    ~Rectangle() {
        // Ownership of the length and width vectors is not transferred to the rectangle.
        // Therefore, the rectangle does not delete the length and width vectors.
    }

    const double length() const {
        return _lengthVec->length();
    }

    const double width() const {
        return _widthVec->length();
    }

    const double area() const override {
        return length() * width();
    }

    const double perimeter() const override {
        return 2 * (length() + width());
    }

    const std::string info() const override {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
    }
};