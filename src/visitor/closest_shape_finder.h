#pragma once

#include "./shape_visitor.h"
#include "../circle.h"
#include "../compound_shape.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "../bounding_box.h"

class ClosestShapeFinder : public ShapeVisitor
{
private:
    double closestDis_ = DBL_MAX;
    Shape* closestShape_ = nullptr;
    CompoundShape* parentShape_ = nullptr;
    BoundingBox _targetBoundingBox;

    void replaceDisAndShape_(const double dis, Shape* shape) {
        if (dis < closestDis_) {
            closestDis_ = dis;
            closestShape_ = shape;
        }
    }

public:
    ClosestShapeFinder(Shape *shape): parentShape_{dynamic_cast<CompoundShape*>(shape)}, _targetBoundingBox{BoundingBox{shape->getPoints()}} {}

    void visitCircle(Circle *circle) override {
        auto circleBoundingBox = BoundingBox{circle->getPoints()};
        const auto dis = _targetBoundingBox.distance(&circleBoundingBox);
        replaceDisAndShape_(dis, circle);
    }

    void visitTriangle(Triangle *triangle) override {
        auto triangleBoundingBox = BoundingBox{triangle->getPoints()};
        const auto dis = _targetBoundingBox.distance(&triangleBoundingBox);
        replaceDisAndShape_(dis, triangle);
    }

    void visitRectangle(Rectangle *rectangle) override {
        auto rectangleBoundingBox = BoundingBox{rectangle->getPoints()};
        const auto dis = _targetBoundingBox.distance(&rectangleBoundingBox);
        replaceDisAndShape_(dis, rectangle);
    }

    void visitCompoundShape(CompoundShape *compoundShape) override {
        auto compoundShapeBoundingBox = BoundingBox{compoundShape->getPoints()};
        // ?
    }

    Shape *getClosestShape() const {
        return closestShape_;
    }

    CompoundShape *getParent() const {
        // ?????????
        return parentShape_;
    }
};
