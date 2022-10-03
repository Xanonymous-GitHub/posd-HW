#pragma once

#include "iterator.h"

class NullIterator : public Iterator {
public:
    void first() const override {}

    const Shape *currentItem() const override {
        return nullptr;
    }

    void next() const override {
        throw MethodShouldNotBeRunError{""};
    }

    bool isDone() const override {
        return true;
    }
};
