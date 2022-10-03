#pragma once

class Iterator;

class Shape {
public:
    virtual double area() const = 0;

    virtual double perimeter() const = 0;

    virtual std::string info() const = 0;

    virtual Iterator *createDFSIterator() const = 0;

    virtual Iterator *createBFSIterator() const = 0;

    virtual void addShape(const Shape *const shape) = 0;

    virtual void deleteShape(const Shape *const shape) = 0;

    virtual ~Shape() {}
};
