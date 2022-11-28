#pragma once

// #include "../iterator.h"
#include "../null_iterator.h"
#include <list>

class Iterator;
class Shape;

class IteratorFactory {
public:
    Iterator *createIterator() const {
        return new NullIterator{};
    }

    virtual Iterator *createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const = 0;
    static IteratorFactory *getInstance(std::string name);
};
