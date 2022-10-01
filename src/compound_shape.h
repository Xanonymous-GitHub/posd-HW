#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "shape.h"

#include <list>

class CompoundShape : public Shape {
private:
    const std::list<const Shape *const> _shapes;

public:
    CompoundShape(const Shape *const shapes[], int size) {}

    ~CompoundShape() {}

    double area() const override {}

    double perimeter() const override {}

    std::string info() const override {}

    const Iterator *createDFSIterator() const override {}

    const Iterator *createBFSIterator() const override {}

    void addShape(const Shape *const shape) override {}

    void deleteShape(const Shape *const shape) override {}
};
