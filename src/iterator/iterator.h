#pragma once

class Shape;

class Iterator {
public:
    virtual ~Iterator() {}

    virtual void first() = 0;

    virtual const Shape *currentItem() const = 0;

    virtual void next() = 0;

    virtual bool isDone() const = 0;

    class MethodShouldNotBeRunError : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
