#pragma once

class Iterator;

class Shape {
public:
    virtual double area() const = 0;

    virtual double perimeter() const = 0;

    virtual std::string info() const = 0;

    virtual Iterator *createIterator(const IteratorFactory *factory) = 0;

    virtual Iterator *createDFSIterator() const = 0;

    virtual Iterator *createBFSIterator() const = 0;

    virtual std::string name() const = 0;

    virtual std::set<const Point *> getPoints() = 0;

    virtual void accept(const ShapeVisitor *visitor) = 0;

    virtual ~Shape() {}

    class MethodShouldNotBeRunError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };

    virtual void addShape(Shape *const shape) {
        throw MethodShouldNotBeRunError("addShape() should not be run");
    };

    virtual void deleteShape(Shape *const shape) {
        throw MethodShouldNotBeRunError("deleteShape() should not be run");
    };
};
