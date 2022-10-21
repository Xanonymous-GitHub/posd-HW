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
    CollisionDetector(const Shape *shape) {}

    void visitCircle(const Circle *circle) override {}

    void visitTriangle(const Triangle *triangle) override {}

    void visitRectangle(const Rectangle *rectangle) override {}

    void visitCompoundShape(const CompoundShape *compoundShape) override {}

    std::vector<Shape *> collidedShapes() const {}
};
