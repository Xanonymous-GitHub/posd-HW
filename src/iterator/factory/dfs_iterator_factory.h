#pragma once

#include "./iterator_factory.h"
#include <list>

class Shape;
class Iterator;

class DFSIteratorFactory : public IteratorFactory {
    virtual Iterator *createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const override;
};
