#pragma once

#include "point.h"
#include <cmath>

class TwoDimensionalVector {
private:
    const Point *_a;
    const Point *_b;

    const double _x_offset() const {
        return _b->x() - _a->x();
    }

    const double _y_offset() const {
        return _b->y() - _a->y();
    }

public:
    TwoDimensionalVector(const Point *a, const Point *b) : _a(a), _b(b) {}

    ~TwoDimensionalVector() {
        // Ownership of the points is not transferred to the vector.
        // Therefore, the vector does not delete the points.
    }

    const Point *a() const {
        return _a;
    }

    const Point *b() const {
        return _b;
    }

    const double length() const {
        return sqrt(_x_offset() * _x_offset() + _y_offset() * _y_offset());
    }

    const double dot(const TwoDimensionalVector *vec) const {
        return _x_offset() * vec->_x_offset() + _y_offset() * vec->_y_offset();
    }

    const double cross(const TwoDimensionalVector *vec) const {
        return _x_offset() * vec->_y_offset() - _y_offset() * vec->_x_offset();
    }

    const std::string info() const {
        return "Vector (" + _a->info() + ", " + _b->info() + ")";
    }

    static const Point *common_point(const TwoDimensionalVector *vec1, const TwoDimensionalVector *vec2) {
        if (vec1->_a == vec2->_a) {
            return vec1->_a;
        } else if (vec1->_a == vec2->_b) {
            return vec1->_a;
        } else if (vec1->_b == vec2->_a) {
            return vec1->_b;
        } else if (vec1->_b == vec2->_b) {
            return vec1->_b;
        } else {
            return nullptr;
        }
    }

    static const Point *other_point(const TwoDimensionalVector *vec, const Point *point) {
        if (vec->_a == point) {
            return vec->_b;
        } else if (vec->_b == point) {
            return vec->_a;
        } else {
            return nullptr;
        }
    }
};