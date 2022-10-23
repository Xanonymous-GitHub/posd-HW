#pragma once

#include "../bounding_box.h"
#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/bfs_iterator_factory.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "shape_visitor.h"
#include <vector>

class CollisionDetector : public ShapeVisitor {
private:
    std::vector<Shape *> _collideResult;
    const BoundingBox *_targetBoundingBox;

public:
    CollisionDetector(const Shape *const shape) {}

    void visitCircle(const Circle *const circle) const override {

    }

    void visitTriangle(const Triangle *const triangle) const override {}

    void visitRectangle(const Rectangle *const rectangle) const override {}

    void visitCompoundShape(const CompoundShape *const compoundShape) const override {}

    std::vector<Shape *> collidedShapes() const {
        return _collideResult;
    }
};
