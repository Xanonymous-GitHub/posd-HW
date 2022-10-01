#pragma once

#include "../shape.h"
#include "iterator.h"

class CompoundShape;

template <class ForwardIterator>
class BFSCompoundIterator : public Iterator {
public:
    BFSCompoundIterator(const ForwardIterator &begin, const ForwardIterator &end) {}

    void first() const override {}

    const Shape *currentItem() const override {}

    void next() const override {}

    bool isDone() const override {}
};
