#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "shape.h"

#include <list>

class CompoundShape : public Shape {
private:
    const std::list<const Shape *> _shapes;

public:
    template <class... MShape>
    requires is_base_type_of<Shape, MShape...>
    CompoundShape(const MShape &...shapes) : _shapes{{&shapes...}} {}

    CompoundShape(const Shape *const shapes[], int size) : _shapes{shapes, shapes + size} {}

    ~CompoundShape() {
        // Ownership of shapes is transferred to the compound shape.
        // Therefore, the compound shape deletes the shapes.
    }

    constexpr double area() const override {
        // TODO: Implement this method.
        return 0.0;
    }

    constexpr double perimeter() const override {
        // TODO: Implement this method.
        return 0.0;
    }

    std::string info() const override {
        auto ss = std::stringstream{};

        std::for_each(_shapes.begin(), --_shapes.end(), [&ss](const Shape *const shape) {
            ss << shape->info() << ", ";
        });

        ss.seekp(-2, std::ios_base::end);

        return "CompoundShape (" + ss.str() + ")";
    }

    const Iterator *createDFSIterator() const override {}

    const Iterator *createBFSIterator() const override {}

    void addShape(const Shape *const shape) override {}

    void deleteShape(const Shape *const shape) override {}
};
