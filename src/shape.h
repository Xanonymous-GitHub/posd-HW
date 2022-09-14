#pragma once

class Shape {
public:
    virtual const double area() const = 0;

    virtual const double perimeter() const = 0;

    virtual const std::string info() const = 0;

    virtual ~Shape() {}
};
