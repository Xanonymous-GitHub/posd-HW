#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "shape.h"

#include <list>

class CompoundShape : public Shape {
private:
    std::list<const Shape *> shapes_;

public:
    template <class... MShape>
    requires is_base_type_of<Shape, MShape...>
    CompoundShape(const MShape &...shapes) : shapes_{&shapes...} {}

    CompoundShape(const Shape *const shapes[], int size) : shapes_{shapes, shapes + size} {}

    ~CompoundShape() {
        // Ownership of shapes is transferred to the compound shape.
        // Therefore, the compound shape deletes the shapes.
    }

    double area() const override {
        double area = 0;

        for (const auto &shape : shapes_) {
            area += shape->area();
        }

        return area;
    }

    double perimeter() const override {
        double perimeter = 0;

        for (const auto &shape : shapes_) {
            perimeter += shape->perimeter();
        }

        return perimeter;
    }

    std::string info() const override {
        auto ss = std::stringstream{};
        const auto lastIndex = shapes_.size() - 1;

        std::for_each(shapes_.cbegin(), shapes_.cend(), [&ss, &lastIndex, i = 0](const Shape *const shape) mutable {
            ss << shape->info();

            if (i < lastIndex) {
                ss << ", ";
            }

            i++;
        });

        return "CompoundShape (" + ss.str() + ")";
    }

    const Iterator *createDFSIterator() const override {}

    const Iterator *createBFSIterator() const override {}

    void addShape(const Shape *const shape) override {
        shapes_.push_back(shape);
    }

    void deleteShape(const Shape *const shape) override {
        shapes_.remove(shape);
    }
};
