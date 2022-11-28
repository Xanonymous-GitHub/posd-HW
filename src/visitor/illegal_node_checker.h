#pragma once

#include "../compound_shape.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "./shape_visitor.h"

class IllegalNodeChecker : public ShapeVisitor {
private:
    bool isIllegal_ = false;

public:
    void visitCircle(Circle *circle) override {
        // ?
    }

    void visitTriangle(Triangle *triangle) override {
        // ?
    }

    void visitRectangle(Rectangle *rectangle) override {
        // ?
    }

    void visitCompoundShape(CompoundShape *compoundShape) override {
        const auto listIteratorFactory = IteratorFactory::getInstance("List");
        const auto compoundShapeListIterator = compoundShape->createIterator(listIteratorFactory);

        // FIXME: remove this line.
        // std::cout<< "@@@@@@@@@@@@@" << std::endl;
        // std::cout<< compoundShapeListIterator->isDone() << std::endl;

        if (compoundShapeListIterator->isDone()) {
            // found compound shape has no child.
            isIllegal_ = true;
            return;
        }

        const auto childA = compoundShapeListIterator->currentItem();
        compoundShapeListIterator->next();

        if (compoundShapeListIterator->isDone() && childA->name() == "CompoundShape") {
            // found compound shape has only one child which is another CompoundShape.
            isIllegal_ = true;
            return;
        }
    }

    bool isIllegal() const {
        return isIllegal_;
    }
};
