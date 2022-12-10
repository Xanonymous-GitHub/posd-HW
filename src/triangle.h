#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <optional>
#include <string>

class Triangle : public Shape {
private:
    const TwoDimensionalVector v1_;
    const TwoDimensionalVector v2_;
    const TwoDimensionalVector v3_;
    const std::string_view name_ = "Triangle";

public:
    Triangle(
        const TwoDimensionalVector &v1,
        // clang-format off
        const TwoDimensionalVector &v2) : v1_{v1}, v2_{v2}, v3_ {
        [&]() -> TwoDimensionalVector {
            if (v1.cross(v2) == 0) {
                throw std::invalid_argument("The triangle is degenerate.");
            }
            const auto common_point = TwoDimensionalVector::common_point(v1, v2);
            if (common_point == std::nullopt) {
                throw std::invalid_argument("no common point");
            }
            const auto non_common_point_a = TwoDimensionalVector::other_point(v1, *common_point);
            const auto non_common_point_b = TwoDimensionalVector::other_point(v2, *common_point);
            return TwoDimensionalVector{*non_common_point_a, *non_common_point_b};
        }()
    } {}
    // clang-format on

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

    Iterator *createDFSIterator() const override {
        return new NullIterator();
    }

    Iterator *createBFSIterator() const override {
        return new NullIterator();
    }

    std::set<Point> getPoints() const override {
        const auto commonPoint = TwoDimensionalVector::common_point(v1_, v2_);
        if (commonPoint == std::nullopt) {
            throw std::invalid_argument("no common point");
        }

        const auto unCommonPointA = TwoDimensionalVector::other_point(v1_, *commonPoint);
        const auto unCommonPointB = TwoDimensionalVector::other_point(v2_, *commonPoint);

        return {*commonPoint, *unCommonPointA, *unCommonPointB};
    }

    void accept(ShapeVisitor *const visitor) override {
        visitor->visitTriangle(this);
    }
};