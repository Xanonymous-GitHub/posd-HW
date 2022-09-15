#pragma once

#include "shape.h"
#include "two_dimensional_vector.h"
#include <string>

class Triangle : public Shape {
private:
    const TwoDimensionalVector *_v1;
    const TwoDimensionalVector *_v2;
    const TwoDimensionalVector *_v3;

public:
    Triangle(
        const TwoDimensionalVector *v1,
        const TwoDimensionalVector *v2) : _v1(v1), _v2(v2) {
        _v3 = new TwoDimensionalVector(v2->b(), v1->b());
    }

    ~Triangle() {
        // Ownership of the vectors is not transferred to the triangle.
        // Therefore, the triangle does not delete the vectors.
    }

    const double area() const override {
        return 0.5 * _v1->cross(_v2);
    }

    const double perimeter() const override {
        return _v1->length() + _v2->length() + _v3->length();
    }

    const std::string info() const override {
        return "Triangle (" + _v1->info() + ", " + _v2->info() + ")";
    }
};