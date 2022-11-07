#pragma once

#include "../illegal_node_iterator.h"
#include "./iterator_factory.h"

class IllegalNodeIteratorFactory : public IteratorFactory {
    Iterator *createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const override {
        return new IllegalNodeIterator{*begin};
    }
};
