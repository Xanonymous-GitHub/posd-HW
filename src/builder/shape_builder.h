#pragma once
#include "../circle.h"
#include "../compound_shape.h"
#include "../rectangle.h"
#include "../triangle.h"
#include <stack>
#include <vector>

class ShapeBuilder {
private:
    std::vector<Shape *> result_{};
    std::stack<CompoundShape *> unfinished_compound_shapes_{};

    template <typename ContainerType>
    void safeDeleteOf_(ContainerType &container) {
        for (auto &el : container) {
            delete el;
        }
    }

    bool isBuildingCompoundShape_() {
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
    void buildCircle(const Point *center, const Point *to_radius) {
        const auto v = new TwoDimensionalVector{center, to_radius};
        auto circle = new Circle{v};
        deliverBuiltShape_(circle);
    }

    void buildTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {
        const auto v1 = new TwoDimensionalVector{common_point, v1_point};
        const auto v2 = new TwoDimensionalVector{common_point, v2_point};
        auto triangle = new Triangle{v1, v2};
        deliverBuiltShape_(triangle);
    }

    void buildRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {
        const auto v1 = new TwoDimensionalVector{common_point, v1_point};
        const auto v2 = new TwoDimensionalVector{common_point, v2_point};
        auto rectangle = new Rectangle{v1, v2};
        deliverBuiltShape_(rectangle);
    }

    void buildCompoundShape() {
        auto compound_shape = new CompoundShape{{}, 0};
        unfinished_compound_shapes_.push(compound_shape);
    }

    void buildCompoundEnd() {
        if (unfinished_compound_shapes_.empty()) {
            return;
        }

        auto compound_shape = unfinished_compound_shapes_.top();
        unfinished_compound_shapes_.pop();

        if (compound_shape != nullptr) {
            deliverBuiltShape_(compound_shape);
        }
    }

    std::vector<Shape *> getResult() {
        std::vector<Shape *> productions_ = result_;
        result_.clear();
        return productions_;
    }

    ~ShapeBuilder() {
        safeDeleteOf_(result_);
        while (!unfinished_compound_shapes_.empty()) {
            auto compound_shape = unfinished_compound_shapes_.top();
            unfinished_compound_shapes_.pop();
            delete compound_shape;
        }
    }
};
