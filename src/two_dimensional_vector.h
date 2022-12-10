#pragma once

#include "point.h"
#include <cmath>
#include <optional>

class TwoDimensionalVector {
private:
    const Point _a;
    const Point _b;

    constexpr double _x_offset() const noexcept {
        return _b.x() - _a.x();
    }

    constexpr double _y_offset() const noexcept {
        return _b.y() - _a.y();
    }

public:
    constexpr TwoDimensionalVector(const Point &a, const Point &b) noexcept : _a{a}, _b{b} {}
    constexpr TwoDimensionalVector(const Point *a, const Point *b) : _a{*a}, _b{*b} {}

    bool operator==(const TwoDimensionalVector &vec) const noexcept {
        return &vec == this || vec.info() == info();
    }

    constexpr Point a() const noexcept {
        return _a;
    }

    constexpr Point b() const noexcept {
        return _b;
    }

    constexpr double length() const noexcept {
        const auto x_offset = _x_offset();
        const auto y_offset = _y_offset();
        return sqrt(x_offset * x_offset + y_offset * y_offset);
    }

    constexpr double dot(const TwoDimensionalVector &vec) const noexcept {
        return _x_offset() * vec._x_offset() + _y_offset() * vec._y_offset();
    }

    constexpr double cross(const TwoDimensionalVector &vec) const noexcept {
        return _x_offset() * vec._y_offset() - _y_offset() * vec._x_offset();
    }

    std::string info() const noexcept {
        return "Vector (" + _a.info() + ", " + _b.info() + ")";
    }

    static const std::optional<Point> common_point(const TwoDimensionalVector &vec1, const TwoDimensionalVector &vec2) noexcept {
        const auto &&a1 = vec1.a();
        const auto &&a2 = vec2.a();

        if (a1 == a2) {
            return a1;
        }

        const auto &&b2 = vec2.b();

        if (a1 == b2) {
            return a1;
        }

        const auto &&b1 = vec1.b();

        if (b1 == a2) {
            return b1;
        }

        if (b1 == b2) {
            return b1;
        }

        return std::nullopt;
    }

    static const std::optional<Point> other_point(const TwoDimensionalVector &vec, const Point &point) noexcept {
        const auto &&a = vec.a();
        const auto &&b = vec.b();

        if (a == point) {
            return b;
        }

        if (b == point) {
            return a;
        }

        return std::nullopt;
    }
};