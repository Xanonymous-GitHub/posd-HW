#pragma once

#include "shape.h"
#include <set>
#include <string>

class BoundingBox {
private:
    const Point rightUpPoint_;
    const Point leftDownPoint_;

    double findMaxX_(const std::set<Point> &points) const noexcept {
        double maxX = -DBL_MAX;
        for (auto &&point : points) {
            if (point.x() > maxX) {
                maxX = point.x();
            }
        }
        return maxX;
    }

    double findMinX_(const std::set<Point> &points) const noexcept {
        double minX = DBL_MAX;
        for (auto &&point : points) {
            if (point.x() < minX) {
                minX = point.x();
            }
        }
        return minX;
    }

    double findMaxY_(const std::set<Point> &points) const noexcept {
        double maxY = -DBL_MAX;
        for (auto &&point : points) {
            if (point.y() > maxY) {
                maxY = point.y();
            }
        }
        return maxY;
    }

    double findMinY_(const std::set<Point> &points) const noexcept {
        double minY = DBL_MAX;
        for (auto &&point : points) {
            if (point.y() < minY) {
                minY = point.y();
            }
        }
        return minY;
    }

public:
    constexpr BoundingBox(const std::set<Point> &points) noexcept : rightUpPoint_{calMaximumPoint(points)},
                                                                    leftDownPoint_{calMinimumPoint(points)} {}

    constexpr Point calMaximumPoint(const std::set<Point> &points) const noexcept {
        const double maxX = findMaxX_(points);
        const double maxY = findMaxY_(points);
        return Point{maxX, maxY};
    }

    constexpr Point calMinimumPoint(const std::set<Point> &points) const noexcept {
        const double minX = findMinX_(points);
        const double minY = findMinY_(points);
        return Point{minX, minY};
    }

    constexpr Point max() const noexcept {
        return rightUpPoint_;
    }

    constexpr Point min() const noexcept {
        return leftDownPoint_;
    }

    bool collide(const BoundingBox *const box) {
        if (box == nullptr) {
            throw std::invalid_argument("The bounding box to collide with cannot be null.");
        }

        return !((box->rightUpPoint_.x() < leftDownPoint_.x()) ||
                 (box->leftDownPoint_.x() > rightUpPoint_.x()) ||
                 (box->rightUpPoint_.y() < leftDownPoint_.y()) ||
                 (box->leftDownPoint_.y() > rightUpPoint_.y()));
    }

    double distance(BoundingBox *box) {
        const auto v1 = TwoDimensionalVector{box->max(), this->max()};
        const auto v2 = TwoDimensionalVector{box->min(), this->min()};
        return v1.length() + v2.length();
    }
};
