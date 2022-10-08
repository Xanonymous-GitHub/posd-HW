#pragma once

#include <queue>

#include "../shape.h"
#include "iterator.h"

class CompoundShape;

template <class ForwardShapeIterator>
class DFSCompoundIterator : public Iterator {
private:
    bool isIterated_ = false;

    const ForwardShapeIterator begin_, end_;

    std::queue<const Shape *> traversed_;
    std::vector<const Shape *> debugTraversedVector_;

    void debugPrint_() const {
        std::cout << "traversed_: ";

        for (const auto &it : debugTraversedVector_) {
            std::cout << it->name() << " ";
        }

        std::cout << std::endl;
    }

    void makeDfsTraversalHistory_() {
        std::for_each(begin_, end_, [&](const Shape *const shape) {
            traversed_.push(shape);

            // TODO: Remove this debug code.
            debugTraversedVector_.push_back(shape);

            // // FIXME: This is a bad solution.
            // std::cout << std::endl
            //           << "@@@@@@@@" << std::endl;
            // debugPrint_();
            // std::cout << "@@@@@@@@" << std::endl
            //           << std::endl;

            const auto currentIt = shape->createDFSIterator();

            if (currentIt->isDone()) {
                return;
            }

            for (currentIt->first(); !currentIt->isDone(); currentIt->next()) {
                traversed_.push(currentIt->currentItem());
                // TODO: Remove this debug code.
                debugTraversedVector_.push_back(currentIt->currentItem());
            }
        });
    }

    void clearTraversed_() {
        while (!traversed_.empty()) {
            traversed_.pop();
        }

        // TODO: Remove this debug code.
        debugTraversedVector_.clear();
    }

public:
    DFSCompoundIterator(const ForwardShapeIterator &begin, const ForwardShapeIterator &end) : begin_{begin}, end_{end} {
        makeDfsTraversalHistory_();
        // debugPrint_();
    }

    void first() override {
        if (isIterated_) {
            clearTraversed_();
            makeDfsTraversalHistory_();
            isIterated_ = false;
        }
    }

    const Shape *currentItem() const override {
        if (!isDone()) {
            return traversed_.front();
        } else {
            throw MethodShouldNotBeRunError{"should not call currentItem(), This iterator is done"};
        }
    }

    void next() override {
        if (!isDone()) {
            traversed_.pop();
            isIterated_ = true;
        } else {
            throw MethodShouldNotBeRunError{"should not call next(), this iterator is done"};
        }
    }

    bool isDone() const override {
        return traversed_.empty();
    }
};
