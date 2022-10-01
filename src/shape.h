#pragma once

class Iterator;

template <typename Base, typename... Derived>
concept is_base_type_of = (std::is_base_of_v<Base, Derived> && ...);

class Shape {
public:
    virtual constexpr double area() const = 0;

    virtual constexpr double perimeter() const = 0;

    virtual std::string info() const = 0;

    virtual const Iterator *createDFSIterator() const = 0;

    virtual const Iterator *createBFSIterator() const = 0;

    virtual void addShape(const Shape *const shape) = 0;

    virtual void deleteShape(const Shape *const shape) = 0;

    virtual ~Shape() {}
};
