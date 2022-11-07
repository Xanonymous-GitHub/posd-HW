#include "./iterator.h"

class IllegalNodeIterator : public Iterator
{
public:
    IllegalNodeIterator(Shape *root) {}

    void first() override {}

    Shape *currentItem() const override {}

    void next() override {}

    bool isDone() const override {}
};
