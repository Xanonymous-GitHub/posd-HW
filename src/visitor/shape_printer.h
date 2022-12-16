#pragma once

#include "../graphics/canvas.h"
#include "shape_visitor.h"
#include <memory>

class ShapePrinter : public ShapeVisitor {
private:
    const std::shared_ptr<Canvas> _canvas;

public:
    ShapePrinter(Canvas *const canvas) : _canvas{canvas} {}

    ShapePrinter(const std::shared_ptr<Canvas> &canvas) : _canvas{canvas} {}

    void visitCircle(Circle *const circle) override {
        _canvas->drawCircle(circle);
    }

    void visitTriangle(Triangle *const triangle) override {
        _canvas->drawTriangle(triangle);
    }

    void visitRectangle(Rectangle *const rectangle) override {
        _canvas->drawRectangle(rectangle);
    }

    void visitCompoundShape(CompoundShape *const compoundShape) override {}
};
