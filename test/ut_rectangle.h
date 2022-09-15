#include "../src/rectangle.h"

class RectangleTest : public ::testing::Test {
protected:
    RectangleTest() : vec1{TwoDimensionalVector(&_a, &_b)}, vec2{TwoDimensionalVector(&_a, &_c)} {}
    const double DEVIATION = 0.0001;
    const TwoDimensionalVector vec1;
    const TwoDimensionalVector vec2;
    const Point _a{0, 0};
    const Point _b{4, 0};
    const Point _c{0, 3};
};

TEST_F(RectangleTest, ShouldCorrectlySetLengthAndWidth) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_EQ(rectangle.length(), 4);
    ASSERT_EQ(rectangle.width(), 3);
}

TEST_F(RectangleTest, ShouldCorrectlyCalculateArea) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_NEAR(rectangle.area(), 12, DEVIATION);
}

TEST_F(RectangleTest, ShouldCorrectlyCalculatePerimeter) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_NEAR(rectangle.perimeter(), 14, DEVIATION);
}

TEST_F(RectangleTest, ShouldCorrectlyPrintInfo) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_EQ(rectangle.info(), "Rectangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
}
