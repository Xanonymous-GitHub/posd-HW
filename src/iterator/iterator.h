#pragma once

#include "../shape.h"

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() const = 0;
    virtual const Shape *currentItem() const = 0;
    virtual void next() const = 0;
    virtual bool isDone() const = 0;
};
