#pragma once

#include <memory>

#include "../graphics/canvas.h"
#include "shape_visitor.h"

class ShapePrinter : public ShapeVisitor {
   private:
    Canvas *_canvas_$view;

   public:
    ShapePrinter(Canvas *const canvas) : _canvas_$view{canvas} {}

    void visitCircle(Circle *const circle) override {
        _canvas_$view->drawCircle(circle);
    }

    void visitTriangle(Triangle *const triangle) override {
        _canvas_$view->drawTriangle(triangle);
    }

    void visitRectangle(Rectangle *const rectangle) override {
        _canvas_$view->drawRectangle(rectangle);
    }

    void visitCompoundShape(CompoundShape *const compoundShape) override {}
};
