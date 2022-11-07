#pragma once

#include "./shape_visitor.h"
#include "../iterator/factory/list_iterator_factory.h"

class IllegalNodeChecker : public ShapeVisitor
{
public:
    void visitCircle(Circle *circle) override {}

    void visitTriangle(Triangle *triangle) override {}

    void visitRectangle(Rectangle *rectangle) override {}

    void visitCompoundShape(CompoundShape *compoundShape) override {}

    bool isIllegal() const {}
};
