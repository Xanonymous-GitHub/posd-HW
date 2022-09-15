#include "../src/triangle.h"

class TriangleTest : public ::testing::Test {
protected:
    TriangleTest() : vec1{TwoDimensionalVector(&_a, &_b)}, vec2{TwoDimensionalVector(&_a, &_c)} {}
    const double DEVIATION = 0.0001;
    const TwoDimensionalVector vec1;
    const TwoDimensionalVector vec2;
    const Point _a{0, 0};
    const Point _b{4, 0};
    const Point _c{0, 3};
};

TEST_F(TriangleTest, ShouldCorrectlyCalculateArea) {
    // Arrange
    const Triangle triangle{&vec1, &vec2};

    // Act
    ASSERT_NEAR(triangle.area(), 6, DEVIATION);
}

TEST_F(TriangleTest, ShouldCorrectlyCalculatePerimeter) {
    // Arrange
    const Triangle triangle{&vec1, &vec2};

    // Act
    ASSERT_NEAR(triangle.perimeter(), 12, DEVIATION);
}

TEST_F(TriangleTest, ShouldCorrectlyPrintInfo) {
    // Arrange
    const Triangle triangle{&vec1, &vec2};

    // Act
    ASSERT_EQ(triangle.info(), "Triangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
}
