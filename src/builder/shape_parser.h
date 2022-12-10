#pragma once

#include "../two_dimensional_vector.h"
#include "./scanner.h"
#include "./shape_builder.h"
#include <array>
#include <cassert>
#include <string>
#include <unordered_map>
#include <vector>

class ShapeParser {
private:
    Scanner scanner_;
    ShapeBuilder builder_{};

    std::array<Point, 3> organizeNext4PointsTo3AndEnsureFirstIsCommonPoint_() {
        const auto scannedPoints = std::array<const Point, 4>{
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
            Point{scanner_.nextDouble(), scanner_.nextDouble()},
        };

        auto infoPointMap = std::unordered_map<std::string, const Point>{};
        auto result$_ = std::array<const Point *, 3>{};

        for (const auto &point : scannedPoints) {
            const auto pointStr = point.info();

            if (infoPointMap.count(pointStr) != 0) {
                result$_.at(0) = new Point{point};
                continue;
            }

            infoPointMap.try_emplace(pointStr, point);
        }

        assert(infoPointMap.size() == 3);

        auto i = 0;
        for (const auto &point : scannedPoints) {
            if (point == *result$_.at(0)) {
                continue;
            }

            result$_.at(++i) = new Point{point};
        }

        const std::array result = {
            *result$_.at(0),
            *result$_.at(1),
            *result$_.at(2),
        };

        // free the memory
        for (auto &&point : result$_) {
            delete point;
        }

        return result;
    }

    void skipNonCompoundEnding_() {
        // skip the `)))` part
        scanner_.next();
        scanner_.next();
        scanner_.next();
    }

    void parseCircle_() {
        auto center = Point{scanner_.nextDouble(), scanner_.nextDouble()};
        auto toRadius = Point{scanner_.nextDouble(), scanner_.nextDouble()};
        builder_.buildCircle(center, toRadius);
        skipNonCompoundEnding_();
    }

    void parseTriangle_() {
        const auto points = organizeNext4PointsTo3AndEnsureFirstIsCommonPoint_();
        builder_.buildTriangle(points.at(0), points.at(1), points.at(2));
        skipNonCompoundEnding_();
    }

    void parseRectangle_() {
        const auto points = organizeNext4PointsTo3AndEnsureFirstIsCommonPoint_();
        builder_.buildRectangle(points.at(0), points.at(1), points.at(2));
        skipNonCompoundEnding_();
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
