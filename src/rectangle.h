#pragma once

#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <string>

class Rectangle : public Shape {
private:
    const TwoDimensionalVector *const _lengthVec;
    const TwoDimensionalVector *const _widthVec;

public:
    Rectangle(
        const TwoDimensionalVector *const lengthVec,
        const TwoDimensionalVector *const widthVec) : _lengthVec(lengthVec), _widthVec(widthVec) {
        if (lengthVec->dot(widthVec) != 0) {
            throw std::invalid_argument("The rectangle is not orthogonal.");
        }

        const auto common_point = TwoDimensionalVector::common_point(lengthVec, widthVec);
        if (common_point == nullptr) {
            throw std::invalid_argument("no common point");
        }
    }

    ~Rectangle() {
        // Ownership of the length and width vectors is not transferred to the rectangle.
        // Therefore, the rectangle does not delete the length and width vectors.
    }

    constexpr double length() const {
        return _lengthVec->length();
    }

    constexpr double width() const {
        return _widthVec->length();
    }

    double area() const override {
        return length() * width();
    }

    double perimeter() const override {
        return 2 * (length() + width());
    }

    std::string info() const override {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
    }

    const Iterator *createDFSIterator() const override {}

    const Iterator *createBFSIterator() const override {}

    void addShape(const Shape *const shape) override {}

    void deleteShape(const Shape *const shape) override {}
};