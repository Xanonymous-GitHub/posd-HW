#pragma once

#include "shape.h"
#include <limits>
#include <set>
#include <string>

class BoundingBox {
private:
    const Point rightUpPoint_;
    const Point leftDownPoint_;

    double findMaxX_(const std::set<Point> &points) const noexcept {
        double maxX = std::numeric_limits<double>::min();
        for (auto &&point : points) {
            if (point.x() > maxX) {
                maxX = point.x();
            }
        }
        return maxX;
    }

    double findMinX_(const std::set<Point> &points) const noexcept {
        double minX = std::numeric_limits<double>::max();
        for (auto &&point : points) {
            if (point.x() < minX) {
                minX = point.x();
            }
        }
        return minX;
    }

    double findMaxY_(const std::set<Point> &points) const noexcept {
        double maxY = std::numeric_limits<double>::min();
        for (auto &&point : points) {
            if (point.y() > maxY) {
                maxY = point.y();
            }
        }
        return maxY;
    }

    double findMinY_(const std::set<Point> &points) const noexcept {
        double minY = std::numeric_limits<double>::max();
        for (auto &&point : points) {
            if (point.y() < minY) {
                minY = point.y();
            }
        }
        return minY;
    }

public:
    BoundingBox(const std::set<Point> &points) noexcept : rightUpPoint_{calMaximumPoint(points)},
                                                          leftDownPoint_{calMinimumPoint(points)} {}

    Point calMaximumPoint(const std::set<Point> &points) const noexcept {
        const double maxX = findMaxX_(points);
        const double maxY = findMaxY_(points);
        return Point{maxX, maxY};
    }

    Point calMinimumPoint(const std::set<Point> &points) const noexcept {
        const double minX = findMinX_(points);
        const double minY = findMinY_(points);
        return Point{minX, minY};
    }

    Point max() const noexcept {
        return rightUpPoint_;
    }

    Point min() const noexcept {
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
