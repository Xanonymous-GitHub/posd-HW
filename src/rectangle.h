#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <optional>
#include <string>

class Rectangle : public Shape {
private:
    TwoDimensionalVector lengthVec_;
    TwoDimensionalVector widthVec_;
    const std::string_view name_ = "Rectangle";

    // get the fourth point of the rectangle.
    const Point findRecPointByCommonAndUncommonPoints_(const Point &commonPoint, const Point &unCommonPointA, const Point &unCommonPointB) const noexcept {
        return Point{
            unCommonPointA.x() + unCommonPointB.x() - commonPoint.x(),
            unCommonPointA.y() + unCommonPointB.y() - commonPoint.y(),
        };
    }

    void verifyOrthogonal(const TwoDimensionalVector &lengthVec, const TwoDimensionalVector &widthVec) const {
        if (lengthVec.dot(widthVec) != 0) {
            throw std::invalid_argument("The rectangle is not orthogonal.");
        }

        const auto common_point = TwoDimensionalVector::common_point(lengthVec, widthVec);
        if (common_point == std::nullopt) {
            throw std::invalid_argument("no common point");
        }
    }

public:
    Rectangle(
        const TwoDimensionalVector &lengthVec,
        const TwoDimensionalVector &widthVec) : lengthVec_{lengthVec}, widthVec_{widthVec} {
        verifyOrthogonal(lengthVec_, widthVec_);
    }

    double length() const noexcept {
        return lengthVec_.length();
    }

    double width() const noexcept {
        return widthVec_.length();
    }

    double area() const override {
        return length() * width();
    }

    double perimeter() const override {
        return 2 * (length() + width());
    }

    std::string info() const override {
        return "Rectangle (" + lengthVec_.info() + ", " + widthVec_.info() + ")";
    }

    std::string_view name() const override {
        return name_;
    }

    std::set<Point> getPoints() const override {
        const auto commonPoint = TwoDimensionalVector::common_point(lengthVec_, widthVec_);
        if (commonPoint == std::nullopt) {
            throw std::invalid_argument("no common point found in rectangle when get points.");
        }

        const auto unCommonPointA = TwoDimensionalVector::other_point(lengthVec_, *commonPoint);
        const auto unCommonPointB = TwoDimensionalVector::other_point(widthVec_, *commonPoint);
        const auto &&lastPoint = findRecPointByCommonAndUncommonPoints_(*commonPoint, *unCommonPointA, *unCommonPointB);

        return {lengthVec_.a(), lengthVec_.b(), widthVec_.a(), widthVec_.b(), lastPoint};
    }

    void accept(ShapeVisitor *const visitor) override {
        visitor->visitRectangle(this);
    }

    void move(const double &deltaX, const double &deltaY) override {
        lengthVec_.move(deltaX, deltaY);
        widthVec_.move(deltaX, deltaY);
    }
};