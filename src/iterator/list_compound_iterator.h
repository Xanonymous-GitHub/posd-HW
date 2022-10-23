#pragma once

#include "./iterator.h"
#include <queue>

template <class ForwardShapeIterator>
class ListCompoundIterator : public Iterator {
private:
    bool isIterated_ = false;

    const ForwardShapeIterator begin_, end_;

    std::queue<const Shape *> traversed_;

    void makeBfsTraversalHistory_() {
        std::for_each(begin_, end_, [&](const Shape *const shape) {
            traversed_.push(shape);
        });

        // // FIXME: This is a bad solution.
        // std::cout << std::endl
        //           << "@@@@@@@@" << std::endl;
        // debugPrint_();
        // std::cout << "@@@@@@@@" << std::endl
        //           << std::endl;
    }

    void clearTraversed_() {
        while (!traversed_.empty()) {
            traversed_.pop();
        }
    }

public:
    ListCompoundIterator(const ForwardShapeIterator &begin, const ForwardShapeIterator &end) : begin_{begin}, end_{end} {
        makeBfsTraversalHistory_();
    }

    void first() override {
        if (isIterated_) {
            clearTraversed_();
            makeBfsTraversalHistory_();
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
            throw MethodShouldNotBeRunError{"should not call next(), This iterator is done"};
        }
    }

    bool isDone() const override {
        return traversed_.empty();
    }
};
