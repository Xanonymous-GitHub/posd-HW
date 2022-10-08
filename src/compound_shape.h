#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "shape.h"

#include <list>

class CompoundShape : public Shape {
private:
    std::list<const Shape *> shapes_;
    const std::string name_ = "CompoundShape";

public:
    template <class... MShape>
    // WARNING: When the size of `shapes` is 1, this constructor will acts in a wrong way.
    CompoundShape(const MShape &...shapes) : shapes_{&shapes...} {}
    CompoundShape(Shape **const shapes, int size) : shapes_{shapes, shapes + size} {}
    CompoundShape(const Shape **const shapes, int size) : shapes_{shapes, shapes + size} {}
    CompoundShape(const Shape *const *const shapes, int size) : shapes_{shapes, shapes + size} {}

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

    std::string name() const override {
        return name_;
    }

    Iterator *createDFSIterator() const override {
        return new DFSCompoundIterator<decltype(shapes_)::const_iterator>{shapes_.cbegin(), shapes_.cend()};
    }

    Iterator *createBFSIterator() const override {
        return new BFSCompoundIterator<decltype(shapes_)::const_iterator>{shapes_.cbegin(), shapes_.cend()};
    }

    void addShape(const Shape *const shape) override {
        shapes_.push_back(shape);
    }

    void deleteShape(const Shape *const shape) override {
        shapes_.erase(
            std::remove_if(
                shapes_.begin(),
                shapes_.end(),
                [&](const Shape *const s) {
                    return s == shape;
                }),
            shapes_.cend() // ^_^
        );
    }
};
