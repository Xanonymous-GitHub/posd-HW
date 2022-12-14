#pragma once

#include "./iterator/factory/iterator_factory.h"
#include <set>

class Iterator;
class Point;
class ShapeVisitor;

class Shape {
public:
    virtual double area() const = 0;

    virtual double perimeter() const = 0;

    virtual std::string info() const = 0;

    virtual Iterator *createIterator(const IteratorFactory *const factory) const {
        return factory->createIterator();
    }

    virtual std::string_view name() const = 0;

    virtual std::set<Point> getPoints() const = 0;

    virtual void accept(ShapeVisitor *const visitor) = 0;

    virtual ~Shape() = default;

    class MethodShouldNotBeRunError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    virtual void addShape(Shape *const shape) {
        throw MethodShouldNotBeRunError("addShape() should not be run");
    };

    virtual void deleteShape(Shape *const shape) {
        throw MethodShouldNotBeRunError("deleteShape() should not be run");
    };

    virtual void force_cleanup_shapes() {}

    virtual void move(const double &deltaX, const double &deltaY) = 0;
};
