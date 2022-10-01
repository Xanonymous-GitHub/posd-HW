#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "shape.h"

#include <list>

class CompoundShape : public Shape {
private:
    const std::list<const Shape *> _shapes;

public:
    CompoundShape(const Shape *const shapes[], int size) {}

    ~CompoundShape() {}

    constexpr double area() const override {
        // TODO: Implement this method.
        return 0.0;
    }

    constexpr double perimeter() const override {
        // TODO: Implement this method.
        return 0.0;
    }

    std::string info() const override {}

    const Iterator *createDFSIterator() const override {}

    const Iterator *createBFSIterator() const override {}

    void addShape(const Shape *const shape) override {}

    void deleteShape(const Shape *const shape) override {}
};
