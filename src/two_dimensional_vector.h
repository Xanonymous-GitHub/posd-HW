#pragma once

#include "point.h"
#include <cmath>

class TwoDimensionalVector {
private:
    const Point *_a;
    const Point *_b;

public:
    TwoDimensionalVector(const Point *a, const Point *b) : _a(a), _b(b) {}

    ~TwoDimensionalVector() {}

    const Point *a() const {}

    const Point *b() const {}

    const double length() const {}

    const double dot(const TwoDimensionalVector *vec) const {}

    const double cross(const TwoDimensionalVector *vec) const {}

    const std::string info() const {}
};