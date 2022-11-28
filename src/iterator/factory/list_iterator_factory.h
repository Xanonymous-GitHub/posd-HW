#pragma once

#include "./iterator_factory.h"
#include <list>

class Shape;
class Iterator;

class ListIteratorFactory : public IteratorFactory {
public:
    virtual Iterator *createIterator(const std::list<Shape *>::const_iterator &begin, const std::list<Shape *>::const_iterator &end) const override;

private:
    ListIteratorFactory() = default;
    friend IteratorFactory *IteratorFactory::getInstance(const std::string &);
};
