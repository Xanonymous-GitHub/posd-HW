#include "../shape.h"
#include "../visitor/illegal_node_checker.h"
#include "./factory/list_iterator_factory.h"
#include "./iterator.h"
#include <list>
#include <queue>

class IllegalNodeIterator : public Iterator {
private:
    bool isIterated_ = false;

    const Shape *root_;

    std::queue<Shape *> traversed_;

    void makeIllegalTraversalHistory_() {
        const auto listIteratorFactory = ListIteratorFactory{};
        const auto listIterator = root_->createIterator(&listIteratorFactory);

        for (listIterator->first(); !listIterator->isDone(); listIterator->next()) {
            const auto shape = listIterator->currentItem();
            // Check if shape is illegal.
            // If yes, then push it to traversed_.
            auto illegalNodeChecker = IllegalNodeChecker{};
            shape->accept(&illegalNodeChecker);
            if (illegalNodeChecker.isIllegal()) {
                traversed_.push(shape);
            }
        }

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
    IllegalNodeIterator(Shape *root) : root_{root} {
        makeIllegalTraversalHistory_();
    }

    void first() override {
        if (isIterated_) {
            clearTraversed_();
            makeIllegalTraversalHistory_();
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
        } else {
            throw MethodShouldNotBeRunError{"should not call next(), This iterator is done"};
        }
    }

    bool isDone() const override {
        return traversed_.empty();
    }
};
