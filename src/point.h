#pragma once

#define MATH_PRECISION_DIGITS 2
#define DEBUGMSG(msg) std::cout << msg << std::endl;

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

class Point {
private:
    const double _x;
    const double _y;

public:
    constexpr Point(const double &x, const double &y) noexcept : _x{x}, _y{y} {}
    constexpr Point(const Point &pt) noexcept : _x{pt.x()}, _y{pt.y()} {}
    constexpr Point(Point &&pt) noexcept : _x{pt.x()}, _y{pt.y()} {}
    constexpr Point() noexcept : _x{0.0}, _y{0.0} {}

    constexpr double x() const noexcept {
        return _x;
    }

    constexpr double y() const noexcept {
        return _y;
    }

    bool operator==(const Point &pt) const noexcept {
        return &pt == this || pt.info() == info();
    }

    bool operator<(const Point &pt) const noexcept {
        return &pt != this && info() < pt.info();
    }

    std::string info() const noexcept {
        auto &&ss = std::stringstream{};
        const auto &&precision = std::setprecision(MATH_PRECISION_DIGITS);
        ss << std::fixed << precision << "(" << _x << ", " << _y << ")";
        return ss.str();
    }
};
