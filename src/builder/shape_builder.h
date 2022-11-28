#pragma once
#include "../circle.h"
#include "../compound_shape.h"
#include "../rectangle.h"
#include "../triangle.h"
#include <vector>

class ShapeBuilder {
private:
    std::vector<Shape *> _result;

public:
    void buildCircle(const Point *center, const Point *to_radius) {}

    void buildTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {}

    void buildRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {}

    void buildCompoundShape() {}

    void buildCompoundEnd() {}

    std::vector<Shape *> getResult() {}
};
