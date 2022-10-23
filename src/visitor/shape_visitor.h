#pragma once

class Circle;
class Triangle;
class Rectangle;
class CompoundShape;

class ShapeVisitor {
public:
    virtual void visitCircle(const Circle *const circle) const = 0;
    virtual void visitTriangle(const Triangle *const triangle) const = 0;
    virtual void visitRectangle(const Rectangle *const rectangle) const = 0;
    virtual void visitCompoundShape(const CompoundShape *const compoundShape) const = 0;
};
