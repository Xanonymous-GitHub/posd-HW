#pragma once

#include "../circle.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../shape.h"
#include "../triangle.h"
#include "../visitor/closest_shape_finder.h"
#include <vector>

class AABBTreeBuilder {
private:
    std::vector<Shape *> tree_;

    void insertShape_(Shape *newShape) {
        if (tree_.empty()) {
            tree_.push_back(newShape);
            return;
        }

        if (tree_.size() == 1) {
            Shape *content_of_compound_shape_[2] = {tree_.front(), newShape};
            CompoundShape compound_shape_{content_of_compound_shape_, 2};
            tree_[0] = &compound_shape_;
        }

        auto closestShapeFinder = ClosestShapeFinder(newShape);

        const auto allShapesIterator = tree_.front()->createDFSIterator();

        for (allShapesIterator->first(); !allShapesIterator->isDone(); allShapesIterator->next()) {
            const auto currentShape = allShapesIterator->currentItem();
            currentShape->accept(&closestShapeFinder);
        }

        const auto closestShape = closestShapeFinder.getClosestShape();
        if (closestShape != nullptr) {
            const auto parent = closestShapeFinder.getParent();
            parent->replace(closestShape, newShape);
        }
    }

public:
    void insertTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {
        const auto v1 = TwoDimensionalVector{common_point, v1_point};
        const auto v2 = TwoDimensionalVector{common_point, v2_point};
        auto triangle = Triangle{&v1, &v2};
        insertShape_(&triangle);
    }

    void insertCircle(const Point *center, const Point *to_radius) {
        const auto v = TwoDimensionalVector{center, to_radius};
        auto circle = Circle{&v};
        insertShape_(&circle);
    }

    void insertRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {
        const auto v1 = TwoDimensionalVector{common_point, v1_point};
        const auto v2 = TwoDimensionalVector{common_point, v2_point};
        auto rectangle = Rectangle{&v1, &v2};
        insertShape_(&rectangle);
    }

    Shape *getTree() const {
        return tree_.front();
    }
};
