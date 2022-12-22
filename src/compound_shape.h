#pragma once

#include "./iterator/bfs_compound_iterator.h"
#include "./iterator/dfs_compound_iterator.h"
#include "./iterator/factory/iterator_factory.h"
#include "./visitor/shape_visitor.h"
#include "point.h"
#include "shape.h"

#include <list>
#include <set>

class CompoundShape : public Shape {
private:
    std::list<Shape *> shapes_;
    const std::string_view name_ = "CompoundShape";

    struct NonValueDuplicateSetComparator_ {
        const bool operator()(const Point &lhs, const Point &rhs) const {
            return lhs.info() < rhs.info();
        }
    };

public:
    template <class... MShape>
    // WARNING: When the size of `shapes` is 1, this constructor will acts in a wrong way.
    constexpr CompoundShape(MShape &...shapes) : shapes_{&shapes...} {}
    CompoundShape(Shape **const shapes, int size) : shapes_{shapes, shapes + size} {}
    // CompoundShape(const Shape **const shapes, int size) : shapes_{shapes, shapes + size} {}
    // CompoundShape(const Shape *const *const shapes, int size) : shapes_{shapes, shapes + size} {}

    ~CompoundShape() {
        // Ownership of shapes is transferred to the compound shape.
        // Therefore, the compound shape deletes the shapes.
        force_cleanup_shapes();
    }

    void force_cleanup_shapes() override {
        for (auto &&s : shapes_) {
            if (s != nullptr) {
                s->force_cleanup_shapes();
            }
        }

        shapes_.clear();
    }

    double area() const override {
        auto &&area = 0.0;

        for (auto &&shape : shapes_) {
            area += shape->area();
        }

        return area;
    }

    double perimeter() const override {
        auto &&perimeter = 0.0;

        for (auto &&shape : shapes_) {
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

    std::string_view name() const override {
        return name_;
    }

    Iterator *createIterator(const IteratorFactory *const factory) const override {
        return factory->createIterator(shapes_.cbegin(), shapes_.cend());
    }

    std::set<Point> getPoints() const override {
        std::set<Point, NonValueDuplicateSetComparator_> points;

        for (auto &&shape : shapes_) {
            const auto shapePoints = shape->getPoints();

            points.insert(shapePoints.cbegin(), shapePoints.cend());
        }

        return std::set<Point>{points.cbegin(), points.cend()};
    }

    void accept(ShapeVisitor *const visitor) override {
        visitor->visitCompoundShape(this);
    }

    void addShape(Shape *const shape) override {
        shapes_.push_back(shape);
    }

    void deleteShape(Shape *const shape) override {
        shapes_.remove(shape);

        for (auto &&s : shapes_) {
            if (s->name() == "CompoundShape") {
                s->deleteShape(shape);
            }
        }
    }

    void replace(Shape *old_shape, Shape *new_shape) {
        std::replace(shapes_.begin(), shapes_.end(), old_shape, new_shape);
    }

    void move(const double &deltaX, const double &deltaY) override {
        for (auto &&it : shapes_) {
            it->move(deltaX, deltaY);
        }
    }
};
