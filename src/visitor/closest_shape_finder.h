#pragma once

#include "./shape_visitor.h"

class ClosestShapeFinder : public ShapeVisitor
{
public:
    ClosestShapeFinder(Shape *shape) {}

    void visitCircle(Circle *circle) override {}

    void visitTriangle(Triangle *triangle) override {}

    void visitRectangle(Rectangle *rectangle) override {}

    void visitCompoundShape(CompoundShape *compoundShape) override {}

    Shape *getClosestShape() const {}

    CompoundShape *getParent() const {}
};
