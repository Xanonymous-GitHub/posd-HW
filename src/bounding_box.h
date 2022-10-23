#pragma once

#include "shape.h"
#include <set>
#include <string>

class BoundingBox {
private:
    const Point rightUpPoint_;
    const Point leftDownPoint_;

    constexpr bool containsPoint_(const Point &point) const {
        return point.x() >= leftDownPoint_.x() && point.x() <= rightUpPoint_.x() &&
               point.y() >= leftDownPoint_.y() && point.y() <= rightUpPoint_.y();
    }

    bool collideInTopLeft_(const BoundingBox &other) const {
        const auto topLeftPoint = Point{other.leftDownPoint_.x(), other.rightUpPoint_.y()};
        return containsPoint_(topLeftPoint);
    }

    bool collideInTopRight_(const BoundingBox &other) const {
        const auto topRightPoint = Point{other.rightUpPoint_.x(), other.rightUpPoint_.y()};
        return containsPoint_(topRightPoint);
    }

    bool collideInBottomLeft_(const BoundingBox &other) const {
        const auto bottomLeftPoint = Point{other.leftDownPoint_.x(), other.leftDownPoint_.y()};
        return containsPoint_(bottomLeftPoint);
    }

    bool collideInBottomRight_(const BoundingBox &other) const {
        const auto bottomRightPoint = Point{other.rightUpPoint_.x(), other.leftDownPoint_.y()};
        return containsPoint_(bottomRightPoint);
    }

    double findMaxX_(const std::set<const Point *> &points) const {
        double maxX = -DBL_MAX;
        for (const auto &point : points) {
            if (point->x() > maxX) {
                maxX = point->x();
            }
        }
        return maxX;
    }

    double findMinX_(const std::set<const Point *> &points) const {
        double minX = DBL_MAX;
        for (const auto &point : points) {
            if (point->x() < minX) {
                minX = point->x();
            }
        }
        return minX;
    }

    double findMaxY_(const std::set<const Point *> &points) const {
        double maxY = -DBL_MAX;
        for (const auto &point : points) {
            if (point->y() > maxY) {
                maxY = point->y();
            }
        }
        return maxY;
    }

    double findMinY_(const std::set<const Point *> &points) const {
        double minY = DBL_MAX;
        for (const auto &point : points) {
            if (point->y() < minY) {
                minY = point->y();
            }
        }
        return minY;
    }

public:
    BoundingBox(const std::set<const Point *> &points) : rightUpPoint_{*calMaximumPoint(points)},
                                                         leftDownPoint_{*calMinimumPoint(points)} {}

    const Point *calMaximumPoint(const std::set<const Point *> &points) const {
        const double maxX = findMaxX_(points);
        const double maxY = findMaxY_(points);
        return new Point{maxX, maxY};
    }

    const Point *calMinimumPoint(const std::set<const Point *> &points) const {
        const double minX = findMinX_(points);
        const double minY = findMinY_(points);
        return new Point{minX, minY};
    }

    constexpr const Point *max() const {
        return &rightUpPoint_;
    }

    constexpr const Point *min() const {
        return &leftDownPoint_;
    }

    bool collide(const BoundingBox *const box) {
        if (box == nullptr) {
            throw std::invalid_argument("The bounding box to collide with cannot be null.");
        }

        return collideInTopLeft_(*box) ||
               collideInTopRight_(*box) ||
               collideInBottomLeft_(*box) ||
               collideInBottomRight_(*box);
    }
};
