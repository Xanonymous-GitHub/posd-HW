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
        int index = 0;

        std::for_each(shapes_.cbegin(), shapes_.cend(), [&](const Shape *const shape) {
            ss << shape->info();

            if (index < lastIndex) {
                ss << ", ";
            }

            index++;
        });

        return "CompoundShape (" + ss.str() + ")";
    }

    Iterator *createDFSIterator() const override {}

    Iterator *createBFSIterator() const override {}

    void addShape(const Shape *const shape) override {
        shapes_.push_back(shape);
    }

    void deleteShape(const Shape *const shape) override {
        bool found = false;

        shapes_.remove_if([&shape, &found](const Shape *const s) {
            return !found && (found = s == shape);
        });
    }
};
