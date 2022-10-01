#pragma once

#include "../shape.h"

template <typename Base, typename... Derived>
concept is_base_type_of = (std::is_base_of_v<Base, Derived> && ...);

class Iterator {
public:
    virtual ~Iterator() {}
    virtual void first() const = 0;
    virtual const Shape *currentItem() const = 0;
    virtual void next() const = 0;
    virtual bool isDone() const = 0;
};
