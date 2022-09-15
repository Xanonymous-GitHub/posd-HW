#pragma once

#define MATH_PRECISION_DIGITS 2

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

class Point {
private:
    const double _x;
    const double _y;

public:
    Point(const double &x, const double &y) : _x{x}, _y{y} {}

    const double x() const {

        return _x;
    }

    const double y() const {
        return _y;
    }

    const bool operator==(const Point &pt) const {
        return &pt == this || pt.info() == info();
    }

    const std::string info() const {
        auto ss = std::stringstream{};
        const auto precision = std::setprecision(MATH_PRECISION_DIGITS);
        ss << std::fixed << precision << "(" << _x << ", " << _y << ")";
        return ss.str();
    }
};
