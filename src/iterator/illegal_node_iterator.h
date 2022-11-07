#include "./iterator.h"
#include <queue>
#include <list>

class IllegalNodeIterator : public Iterator
{
private:
    bool isIterated_ = false;

    const std::list::iterator begin_, end_;

    std::queue<Shape *> traversed_;

    void makeBfsTraversalHistory_() {
        std::for_each(begin_, end_, [&](Shape *const shape) {

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
    IllegalNodeIterator(Shape *root) {
        if (root->name() == "CompoundShape") {

        }
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
        } else {
            throw MethodShouldNotBeRunError{"should not call next(), This iterator is done"};
        }
    }

    bool isDone() const override {
        return traversed_.empty();
    }
};
