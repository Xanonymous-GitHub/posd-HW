#pragma once

class Circle;
class Triangle;
class Rectangle;
class CompoundShape;

class ShapeVisitor {
public:
    virtual void visitCircle(Circle *const circle) = 0;
    virtual void visitTriangle(Triangle *const triangle) = 0;
    virtual void visitRectangle(Rectangle *const rectangle) = 0;
    virtual void visitCompoundShape(CompoundShape *const compoundShape) = 0;
};
