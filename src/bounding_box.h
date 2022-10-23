#pragma once

#include "shape.h"
#include <set>
#include <string>

class BoundingBox {
private:
    const Point *const _max;
    const Point *const _min;

public:
    BoundingBox(const std::set<const Point *> &points) {}

    const Point *calMaximumPoint(const std::set<const Point *> &points) {}

    const Point *calMinimumPoint(const std::set<const Point *> &points) {}

    constexpr const Point *max() {
        return _max;
    }

    constexpr const Point *min() {
        return _min;
    }

    bool collide(const BoundingBox *const box) {}
};
