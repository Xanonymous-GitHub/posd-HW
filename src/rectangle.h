#pragma once

#include "./visitor/shape_visitor.h"
#include "iterator/null_iterator.h"
#include "shape.h"
#include "two_dimensional_vector.h"
#include <string>

class Rectangle : public Shape {
private:
    const TwoDimensionalVector *const _lengthVec;
    const TwoDimensionalVector *const _widthVec;
    const std::string name_ = "Rectangle";

    // get the fourth point of the rectangle.
    const Point *findRecPointByCommonAndUncommonPoints_(const Point &commonPoint, const Point &unCommonPointA, const Point &unCommonPointB) const {
        const auto x = unCommonPointA.x() + unCommonPointB.x() - commonPoint.x();
        const auto y = unCommonPointA.y() + unCommonPointB.y() - commonPoint.y();
        return new Point(x, y);
    }

public:
    Rectangle(
        const TwoDimensionalVector *const lengthVec,
        const TwoDimensionalVector *const widthVec) : _lengthVec(lengthVec), _widthVec(widthVec) {
        if (lengthVec->dot(widthVec) != 0) {
            throw std::invalid_argument("The rectangle is not orthogonal.");
        }

        const auto common_point = TwoDimensionalVector::common_point(lengthVec, widthVec);
        if (common_point == nullptr) {
            throw std::invalid_argument("no common point");
        }
    }

    ~Rectangle() {
        // Ownership of the length and width vectors is not transferred to the rectangle.
        // Therefore, the rectangle does not delete the length and width vectors.
    }

    constexpr double length() const {
        return _lengthVec->length();
    }

    constexpr double width() const {
        return _widthVec->length();
    }

    double area() const override {
        return length() * width();
    }

    double perimeter() const override {
        return 2 * (length() + width());
    }

    std::string info() const override {
        return "Rectangle (" + _lengthVec->info() + ", " + _widthVec->info() + ")";
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
        const auto commonPoint = TwoDimensionalVector::common_point(_lengthVec, _widthVec);
        const auto unCommonPointA = TwoDimensionalVector::other_point(_lengthVec, commonPoint);
        const auto unCommonPointB = TwoDimensionalVector::other_point(_widthVec, commonPoint);
        const auto lastPoint = findRecPointByCommonAndUncommonPoints_(*commonPoint, *unCommonPointA, *unCommonPointB);
        return {commonPoint, unCommonPointA, unCommonPointB, lastPoint};
    }

    void accept(ShapeVisitor *const visitor) override {
        visitor->visitRectangle(this);
    }
};