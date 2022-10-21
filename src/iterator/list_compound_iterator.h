#pragma once

#include "./iterator.h"

template <class ForwardIterator>
class ListCompoundIterator : public Iterator {
public:
    ListCompoundIterator(const ForwardIterator &begin, const ForwardIterator &end) {}

    void first() override {}

    const Shape *currentItem() const override {}

    void next() override {}

    bool isDone() const override {}
};
