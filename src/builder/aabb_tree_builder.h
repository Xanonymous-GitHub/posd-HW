#pragma once

#include "../shape.h"
#include "../triangle.h"
#include "../circle.h"
#include "../iterator/factory/list_iterator_factory.h"
#include "../visitor/closest_shape_finder.h"

class AABBTreeBuilder
{

public:
    void insertTriangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {}

    void insertCircle(const Point *center, const Point *to_radius) {}

    void insertRectangle(const Point *common_point, const Point *v1_point, const Point *v2_point) {}

    Shape *getTree() const {}
};
