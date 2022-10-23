#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <cmath>
#include <string>

class Circle : public Shape {
private:
    const TwoDimensionalVector *const _radiusVec;
    const std::string name_ = "Circle";

    constexpr const Point *center_() const {
        return _radiusVec->a();
    }

public:
    Circle(const TwoDimensionalVector *const radiusVec) : _radiusVec(radiusVec) {}

    ~Circle() {
        // Ownership of the radius vector is not transferred to the circle.
        // Therefore, the circle does not delete the radius vector.
    }

    constexpr double radius() const {
        return _radiusVec->length();
    }

    double area() const override {
        const double myRadius = radius();
        return M_PI * myRadius * myRadius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius();
    }

    std::string info() const override {
        return "Circle (" + _radiusVec->info() + ")";
    }

    std::string name() const override {
        return name_;
    }

    std::set<const Point *> getPoints() const override {
        const auto leftDownPoint = new Point(center_()->x() - radius(), center_()->y() - radius());
        const auto rightUpPoint = new Point(center_()->x() + radius(), center_()->y() + radius());
        return {leftDownPoint, rightUpPoint};
    }

    void accept(ShapeVisitor *const visitor) const override {
        visitor->visitCircle(this);
    }

    Iterator *createDFSIterator() const override {
        return new NullIterator();
    }

    Iterator *createBFSIterator() const override {
        return new NullIterator();
    }
};