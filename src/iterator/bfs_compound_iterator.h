#pragma once

#include "../shape.h"
#include "iterator.h"

class CompoundShape;

template <class ForwardIterator>
requires is_base_type_of<Iterator, ForwardIterator>
class BFSCompoundIterator : public Iterator {
public:
    BFSCompoundIterator(const ForwardIterator &begin, const ForwardIterator &end) {}

    void first() const override {}

    const Shape *currentItem() const override {}

    void next() const override {}

    bool isDone() const override {}
};
