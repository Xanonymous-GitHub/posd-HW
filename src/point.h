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

    double x() const {
        return _x;
    }

    double y() const {
        return _y;
    }

    bool operator==(const Point &pt) const {
        return &pt == this || pt.info() == info();
    }

    std::string info() const {
        auto ss = std::stringstream{};
        const auto precision = std::setprecision(MATH_PRECISION_DIGITS);
        ss << std::fixed << precision << "(" << _x << ", " << _y << ")";
        return ss.str();
    }
};
