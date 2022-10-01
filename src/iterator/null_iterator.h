#pragma once

#include "iterator.h"

class NullIterator : public Iterator {
public:
    void first() const override {}

    const Shape *currentItem() const override {}

    void next() const override {}

    bool isDone() const override {}
};
