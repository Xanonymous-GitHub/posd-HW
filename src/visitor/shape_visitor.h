#pragma once

class Circle;
class Triangle;
class Rectangle;
class CompoundShape;

class ShapeVisitor {
public:
    virtual void visitCircle(const Circle *const circle) = 0;
    virtual void visitTriangle(const Triangle *const triangle) = 0;
    virtual void visitRectangle(const Rectangle *const rectangle) = 0;
    virtual void visitCompoundShape(const CompoundShape *const compoundShape) = 0;
};
