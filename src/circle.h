#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <cmath>
#include <string>

class Circle : public Shape {
private:
    TwoDimensionalVector radiusVec_;
    const std::string_view name_ = "Circle";

public:
    Circle(const TwoDimensionalVector &radiusVec) noexcept : radiusVec_{radiusVec} {}

    double radius() const noexcept {
        return radiusVec_.length();
    }

    Point center() const noexcept {
        return radiusVec_.a();
    }

    double area() const override {
        const auto &&myRadius = radius();
        return M_PI * myRadius * myRadius;
    }

    double perimeter() const override {
        return 2 * M_PI * radius();
    }

    std::string info() const override {
        return "Circle (" + radiusVec_.info() + ")";
    }

    std::string_view name() const override {
        return name_;
    }

    std::set<Point> getPoints() const override {
        const auto &&myCenter = center();
        const auto &&myRadius = radius();

        const auto &&myCenterX = myCenter.x();
        const auto &&myCenterY = myCenter.y();

        return {
            Point(myCenterX - myRadius, myCenterY - myRadius),
            Point(myCenterX + myRadius, myCenterY + myRadius),
        };
    }

    void accept(ShapeVisitor *const visitor) override {
        visitor->visitCircle(this);
    }

    void move(const double &deltaX, const double &deltaY) override {
        radiusVec_.move(deltaX, deltaY);
    }
};