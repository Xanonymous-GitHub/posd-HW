#pragma once

#include "../two_dimensional_vector.h"
#include "./scanner.h"
#include "./shape_builder.h"
#include <string>
#include <vector>

class ShapeParser {
private:
    Scanner *_scanner;
    ShapeBuilder *_builder;

public:
    ShapeParser(std::string input) {}

    ~ShapeParser() {}

    void parse() {}

    std::vector<Shape *> getResult() {}
};
