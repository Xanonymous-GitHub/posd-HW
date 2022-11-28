#pragma once

#include "../two_dimensional_vector.h"
#include "./scanner.h"
#include "./shape_builder.h"
#include <string>
#include <vector>

class ShapeParser {
private:
    Scanner scanner_;
    ShapeBuilder builder_{};

    void parseCircle_() {
        auto center = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto toRadius = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        builder_.buildCircle(center, toRadius);
    }

    void parseTriangle_() {
        auto commonPoint = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto v1Point = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto v2Point = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        builder_.buildTriangle(commonPoint, v1Point, v2Point);
    }

    void parseRectangle_() {
        auto commonPoint = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto v1Point = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto v2Point = new Point{scanner_.nextDouble(), scanner_.nextDouble()};
        builder_.buildRectangle(commonPoint, v1Point, v2Point);
    }

public:
    ShapeParser(const std::string &input) : scanner_{input} {}

    ~ShapeParser() {}

    void parse() {
        while (!scanner_.isDone()) {
            const auto token = scanner_.next();

            if (token == "Circle") {
                parseCircle_();
            } else if (token == "Triangle") {
                parseTriangle_();
            } else if (token == "Rectangle") {
                parseRectangle_();
            } else if (token == "CompoundShape") {
                builder_.buildCompoundShape();
                scanner_.next(); // skip '('
            } else if (token == ")") {
                builder_.buildCompoundEnd();
            }
        }
    }

    std::vector<Shape *> getResult() {
        return builder_.getResult();
    }
};
