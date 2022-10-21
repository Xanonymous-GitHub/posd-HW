#pragma once

#include "shape.h"
#include <set>
#include <string>

class BoundingBox {
private:
    const Point *const _max;
    const Point *const _min;

public:
    BoundingBox(std::set<const Point *> points) {}

    const Point *calMaximumPoint(const std::set<const Point *> points) {}

    const Point *calMinimumPoint(const std::set<const Point *> points) {}

    const Point *max() {}

    const Point *min() {}

    bool collide(const BoundingBox *box) {}
};
