#pragma once

class Circle;
class Triangle;
class Rectangle;

class Canvas {
public:
    virtual ~Canvas() = default;
    virtual void drawCircle(const Circle *const cir) const = 0;
    virtual void drawTriangle(const Triangle *const tri) const = 0;
    virtual void drawRectangle(const Rectangle *const rect) const = 0;
    virtual void display() const = 0;
};