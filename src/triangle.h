#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <optional>
#include <string>

class Triangle : public Shape {
private:
    TwoDimensionalVector v1_;
    TwoDimensionalVector v2_;
    TwoDimensionalVector v3_;
    const std::string_view name_ = "Triangle";

    TwoDimensionalVector generateV3_(const TwoDimensionalVector &v1, const TwoDimensionalVector &v2) const {
        if (v1.cross(v2) == 0) {
            throw std::invalid_argument("The triangle is degenerate.");
        }

        const auto common_point = TwoDimensionalVector::common_point(v1, v2);
        if (common_point == std::nullopt) {
            throw std::invalid_argument("no common point");
        }

        const auto non_common_point_a = TwoDimensionalVector::other_point(v1, *common_point);
        const auto non_common_point_b = TwoDimensionalVector::other_point(v2, *common_point);
        return {*non_common_point_a, *non_common_point_b};
    }

public:
    Triangle(
        const TwoDimensionalVector &v1,
        const TwoDimensionalVector &v2) : v1_{v1}, v2_{v2}, v3_{generateV3_(v1, v2)} {}

    double area() const override {
        return abs(0.5 * v1_.cross(v2_));
    }

    double perimeter() const override {
        return v1_.length() + v2_.length() + v3_.length();
    }

    std::string info() const override {
        return "Triangle (" + v1_.info() + ", " + v2_.info() + ")";
    }

    std::string_view name() const override {
        return name_;
    }

    std::set<Point> getPoints() const override {
        const auto commonPoint = TwoDimensionalVector::common_point(v1_, v2_);
        if (commonPoint == std::nullopt) {
            throw std::invalid_argument("no common point");
        }

        const auto unCommonPointA = TwoDimensionalVector::other_point(v1_, *commonPoint);
        const auto unCommonPointB = TwoDimensionalVector::other_point(v2_, *commonPoint);

        return {v1_.a(), v1_.b(), v2_.a(), v2_.b()};
    }

    void accept(ShapeVisitor *const visitor) override {
        visitor->visitTriangle(this);
    }

    void move(const double &deltaX, const double &deltaY) override {
        v1_.move(deltaX, deltaY);
        v2_.move(deltaX, deltaY);
        v3_.move(deltaX, deltaY);
    }
};