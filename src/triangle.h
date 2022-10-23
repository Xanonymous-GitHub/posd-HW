#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <string>

class Triangle : public Shape {
private:
    const TwoDimensionalVector *const _v1;
    const TwoDimensionalVector *const _v2;
    const TwoDimensionalVector *_v3;
    const std::string name_ = "Triangle";

public:
    Triangle(
        const TwoDimensionalVector *const v1,
        const TwoDimensionalVector *const v2) : _v1(v1), _v2(v2) {
        if (v1->cross(v2) == 0) {
            throw std::invalid_argument("The triangle is degenerate.");
        }

        const auto common_point = TwoDimensionalVector::common_point(v1, v2);
        if (common_point == nullptr) {
            throw std::invalid_argument("no common point");
        }

        const auto non_common_point_a = TwoDimensionalVector::other_point(v1, common_point);
        const auto non_common_point_b = TwoDimensionalVector::other_point(v2, common_point);

        _v3 = new TwoDimensionalVector(non_common_point_a, non_common_point_b);
    }

    ~Triangle() {
        // Ownership of the vectors is not transferred to the triangle.
        // Therefore, the triangle does not delete the vectors.
    }

    double area() const override {
        return abs(0.5 * _v1->cross(_v2));
    }

    double perimeter() const override {
        return _v1->length() + _v2->length() + _v3->length();
    }

    std::string info() const override {
        return "Triangle (" + _v1->info() + ", " + _v2->info() + ")";
    }

    std::string name() const override {
        return name_;
    }

    Iterator *createDFSIterator() const override {
        return new NullIterator();
    }

    Iterator *createBFSIterator() const override {
        return new NullIterator();
    }

    std::set<const Point *> getPoints() const override {
        const auto commonPoint = TwoDimensionalVector::common_point(_v1, _v2);
        const auto unCommonPointA = TwoDimensionalVector::other_point(_v1, commonPoint);
        const auto unCommonPointB = TwoDimensionalVector::other_point(_v2, commonPoint);
        return {commonPoint, unCommonPointA, unCommonPointB};
    }

    void accept(ShapeVisitor *const visitor) const override {
        visitor->visitTriangle(this);
    }
};