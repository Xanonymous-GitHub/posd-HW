#pragma once

#include "../bounding_box.h"
#include "../circle.h"
#include "../compound_shape.h"
#include "../iterator/factory/bfs_iterator_factory.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "shape_visitor.h"
#include <algorithm>
#include <vector>

class CollisionDetector : public ShapeVisitor {
private:
    std::vector<Shape *> _collideResult;
    const BoundingBox _targetBoundingBox;

public:
    CollisionDetector(const Shape *const shape) : _targetBoundingBox{BoundingBox{shape->getPoints()}} {}

    void visitCircle(Circle *const circle) override {
        auto circleBoundingBox = BoundingBox{circle->getPoints()};
        if (circleBoundingBox.collide(&_targetBoundingBox)) {
            _collideResult.push_back(circle);
        }
    }

    void visitTriangle(Triangle *const triangle) override {
        auto triangleBoundingBox = BoundingBox{triangle->getPoints()};
        if (triangleBoundingBox.collide(&_targetBoundingBox)) {
            _collideResult.push_back(triangle);
        }
    }

    void visitRectangle(Rectangle *const rectangle) override {
        auto rectangleBoundingBox = BoundingBox{rectangle->getPoints()};
        if (rectangleBoundingBox.collide(&_targetBoundingBox)) {
            _collideResult.push_back(rectangle);
        }
    }

    void visitCompoundShape(CompoundShape *const compoundShape) override {
        auto compoundShapeBoundingBox = BoundingBox{compoundShape->getPoints()};
        if (compoundShapeBoundingBox.collide(&_targetBoundingBox)) {
            const auto listIteratorFactory = ListIteratorFactory{};
            const auto compoundShapeListIterator = compoundShape->createIterator(&listIteratorFactory);
            for (; !compoundShapeListIterator->isDone(); compoundShapeListIterator->next()) {
                const auto current = compoundShapeListIterator->currentItem();
                current->accept(this);
            }
        }
    }

    std::vector<Shape *> collidedShapes() const {
        // convert all elements from const Shape * to Shape *.
        // We insist that the returned vector contains only non-const Shape *.
        //
        // We can't! Um? Why not? The following code is not allowed:
        //
        // std::vector<Shape *> result;
        // std::transform(_collideResult.cbegin(), _collideResult.cend(), std::back_inserter(result),
        //                [](const Shape *const shape) { return const_cast<Shape *>(shape); });
        // return result;
        return _collideResult;
    }
};
