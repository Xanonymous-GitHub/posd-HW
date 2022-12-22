#pragma once
#include "../circle.h"
#include "../compound_shape.h"
#include "../rectangle.h"
#include "../triangle.h"
#include <algorithm>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

class ShapeBuilder {
private:
    std::vector<Shape *> result_{};
    std::stack<CompoundShape *> unfinished_compound_shapes_{};

    template <typename StackContainerType>
    void safeDeleteStackOf_(StackContainerType &stack_container) {
        while (!stack_container.empty()) {
            auto el = stack_container.top();
            stack_container.pop();
            delete el;
        }
    }

    bool isBuildingCompoundShape_() const {
        return !unfinished_compound_shapes_.empty();
    }

    void deliverBuiltShape_(Shape *const shape) {
        if (isBuildingCompoundShape_()) {
            unfinished_compound_shapes_.top()->addShape(shape);
        } else {
            result_.push_back(shape);
        }
    }

public:
    void buildCircle(const Point &center, const Point &to_radius) {
        const auto s = new Circle{{center, to_radius}};
        deliverBuiltShape_(s);
    }

    void buildTriangle(const Point &common_point, const Point &v1_point, const Point &v2_point) {
        const auto s = new Triangle{
            {common_point, v1_point},
            {common_point, v2_point},
        };
        deliverBuiltShape_(s);
    }

    void buildRectangle(const Point &common_point, const Point &v1_point, const Point &v2_point) {
        const auto s = new Rectangle{
            {common_point, v1_point},
            {common_point, v2_point},
        };
        deliverBuiltShape_(s);
    }

    void buildCompoundShape() {
        // const Shape *empty_shapes[0] = {};
        unfinished_compound_shapes_.push(new CompoundShape{{}, 0});
    }

    void buildCompoundEnd() {
        if (unfinished_compound_shapes_.empty()) {
            return;
        }

        auto &c = unfinished_compound_shapes_.top();
        unfinished_compound_shapes_.pop();

        deliverBuiltShape_(c);
    }

    void destructAllResultsAndBuildingCompounds() {
        // for (auto &&shape : result_) {
        //     if (shape != nullptr) {
        //         shape->force_cleanup_shapes();
        //     }
        // }

        result_.clear();
        safeDeleteStackOf_(unfinished_compound_shapes_);
    }

    std::vector<Shape *> getResult() {
        return result_;
    }

    ~ShapeBuilder() {
        destructAllResultsAndBuildingCompounds();
    }
};
