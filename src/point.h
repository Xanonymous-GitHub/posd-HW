#pragma once

#define MATH_PRECISION_DIGITS 2
#define DEBUGMSG(msg) std::cout << msg << std::endl;

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

class Point {
private:
    double _x;
    double _y;

public:
    Point(const double &x, const double &y) noexcept : _x{x}, _y{y} {}
    Point(const Point &pt) noexcept : _x{pt.x()}, _y{pt.y()} {}
    Point(Point &&pt) noexcept : _x{pt.x()}, _y{pt.y()} {}
    Point() noexcept : _x{0.0}, _y{0.0} {}

    double x() const noexcept {
        return _x;
    }

    double y() const noexcept {
        return _y;
    }

    bool operator==(const Point &pt) const noexcept {
        return pt.info() == info();
    }

    bool operator<(const Point &pt) const noexcept {
        return _x < pt.x() || (_x == pt.x() && _y < pt.y());
    }

    std::string info() const noexcept {
        auto &&ss = std::stringstream{};
        const auto &&precision = std::setprecision(MATH_PRECISION_DIGITS);
        ss << std::fixed << precision << "(" << _x << ", " << _y << ")";
        return ss.str();
    }

    void move(const double &deltaX, const double &deltaY) noexcept {
        _x += deltaX;
        _y += deltaY;
    }
};
