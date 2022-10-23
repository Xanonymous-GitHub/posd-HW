#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/factory/iterator_factory.h"
#include "./visitor/shape_visitor.h"
#include "shape.h"

#include <list>

class CompoundShape : public Shape {
private:
    std::list<Shape *> shapes_;
    const std::string name_ = "CompoundShape";

    struct NonValueDuplicateSetComparator_ {
        const bool operator()(const Point *const lhs, const Point *const rhs) const {
            return lhs->info() < rhs->info();
        }
    };

public:
    template <class... MShape>
    // WARNING: When the size of `shapes` is 1, this constructor will acts in a wrong way.
    CompoundShape(MShape &...shapes) : shapes_{&shapes...} {}
    CompoundShape(Shape **const shapes, int size) : shapes_{shapes, shapes + size} {}
    // CompoundShape(const Shape **const shapes, int size) : shapes_{shapes, shapes + size} {}
    // CompoundShape(const Shape *const *const shapes, int size) : shapes_{shapes, shapes + size} {}

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

    Iterator *createIterator(const IteratorFactory *const factory) const override {
        return factory->createIterator(shapes_.cbegin(), shapes_.cend());
    }

    Iterator *createDFSIterator() const override {
        return new DFSCompoundIterator<decltype(shapes_)::const_iterator>{shapes_.cbegin(), shapes_.cend()};
    }

    Iterator *createBFSIterator() const override {
        return new BFSCompoundIterator<decltype(shapes_)::const_iterator>{shapes_.cbegin(), shapes_.cend()};
    }

    std::set<const Point *> getPoints() const override {
        std::set<const Point *, NonValueDuplicateSetComparator_> points;

        for (const auto &shape : shapes_) {
            const auto shapePoints = shape->getPoints();

            points.insert(shapePoints.cbegin(), shapePoints.cend());
        }

        return std::set<const Point *>(points.cbegin(), points.cend());
    }

    void accept(ShapeVisitor *const visitor) const override {
        visitor->visitCompoundShape(this);
    }

    void addShape(Shape *const shape) override {
        shapes_.push_back(shape);
    }

    void deleteShape(Shape *const shape) override {
        shapes_.remove(shape);

        for (const auto &s : shapes_) {
            if (s->name() == "CompoundShape") {
                s->deleteShape(shape);
            }
        }
    }
};
