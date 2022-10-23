#pragma once

#include "../list_compound_iterator.h"
#include "./iterator_factory.h"

class ListIteratorFactory : public IteratorFactory {
    Iterator *createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const {
        return new ListCompoundIterator{begin, end};
    }
};
