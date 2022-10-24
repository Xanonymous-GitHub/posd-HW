#pragma once

#include "iterator.h"

class NullIterator : public Iterator {
public:
    void first() override {
        throw MethodShouldNotBeRunError{"first() should not be run"};
    }

    Shape *currentItem() const override {
        throw MethodShouldNotBeRunError{"currentItem() should not be run"};
    }

    void next() override {
        throw MethodShouldNotBeRunError{"next() should not be run"};
    }

    bool isDone() const override {
        return true;
    }
};
