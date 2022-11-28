#pragma once

#include "./iterator.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

template <class ForwardShapeIterator>
class ListCompoundIterator : public Iterator {
private:
    bool isIterated_ = false;

    const ForwardShapeIterator begin_, end_;

    std::queue<Shape *> traversed_;
    std::vector<Shape *> debugTraversedVector_;

    void debugPrint_() const {
        std::cout << "traversed_: ";

        for (const auto &it : debugTraversedVector_) {
            std::cout << it->name() << " ";
        }

        for (const auto &it : debugTraversedVector_) {
            std::cout << it->info() << std::endl;
        }

        std::cout << std::endl;
    }

    void makeBfsTraversalHistory_() {
        std::for_each(begin_, end_, [&](Shape *const shape) {
            if (shape != nullptr) {
                traversed_.push(shape);

                // TODO: Remove this debug code.
                debugTraversedVector_.push_back(shape);
            }
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

        // TODO: Remove this debug code.
        debugTraversedVector_.clear();
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

    Shape *currentItem() const override {
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

            // Erase the first element of the debug vector.
            debugTraversedVector_.front() = std::move(debugTraversedVector_.back());
            debugTraversedVector_.pop_back();
        } else {
            throw MethodShouldNotBeRunError{"should not call next(), This iterator is done"};
        }
    }

    bool isDone() const override {
        return traversed_.empty();
    }
};
