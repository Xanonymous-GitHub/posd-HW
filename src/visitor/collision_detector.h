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
    std::vector<const Shape *> _collideResult;
    const BoundingBox *_targetBoundingBox;

public:
    CollisionDetector(const Shape *const shape) {}

    void visitCircle(const Circle *const circle) override {
        auto circleBoundingBox = BoundingBox{circle->getPoints()};
        if (circleBoundingBox.collide(_targetBoundingBox)) {
            _collideResult.push_back(circle);
        }
    }

    void visitTriangle(const Triangle *const triangle) override {
        auto triangleBoundingBox = BoundingBox{triangle->getPoints()};
        if (triangleBoundingBox.collide(_targetBoundingBox)) {
            _collideResult.push_back(triangle);
        }
    }

    void visitRectangle(const Rectangle *const rectangle) override {
        auto rectangleBoundingBox = BoundingBox{rectangle->getPoints()};
        if (rectangleBoundingBox.collide(_targetBoundingBox)) {
            _collideResult.push_back(rectangle);
        }
    }

    void visitCompoundShape(const CompoundShape *const compoundShape) override {
        auto compoundShapeBoundingBox = BoundingBox{compoundShape->getPoints()};
        if (compoundShapeBoundingBox.collide(_targetBoundingBox)) {
            _collideResult.push_back(compoundShape);
        }
    }

    std::vector<const Shape *> collidedShapes() const {
        return _collideResult;
    }
};
