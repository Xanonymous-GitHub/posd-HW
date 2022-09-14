#pragma once

#include <cmath>

class Point {
private:
    const double _x;
    const double _y;

public:
    Point(double x, double y) : _x(x), _y(y) {}

    ~Point() {}

    const double x() const {}

    const double y() const {}

    const bool operator==(const Point &pt) const {}

    const std::string info() const {}
};
