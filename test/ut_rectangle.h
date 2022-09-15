#include "../src/rectangle.h"

class RectangleTest : public ::testing::Test {
protected:
    RectangleTest() : vec1{TwoDimensionalVector(&_a, &_b)}, vec2{TwoDimensionalVector(&_b, &_c)} {}
    const double DEVIATION = 0.0001;
    const TwoDimensionalVector vec1;
    const TwoDimensionalVector vec2;
    const Point _a{-5, 9};
    const Point _b{3, 4};
    const Point _c{3, 9};
    const Point _d{-5, 4};
};

TEST_F(RectangleTest, ShouldCorrectlySetLengthAndWidth) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_EQ(rectangle.length(), 9.433981132056603);
    ASSERT_EQ(rectangle.width(), 5);
}

TEST_F(RectangleTest, ShouldCorrectlyCalculateArea) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_NEAR(rectangle.area(), 47.169905660283014, DEVIATION);
}

TEST_F(RectangleTest, ShouldCorrectlyCalculatePerimeter) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_NEAR(rectangle.perimeter(), 28.867962264113206, DEVIATION);
}

TEST_F(RectangleTest, ShouldCorrectlyPrintInfo) {
    // Arrange
    const Rectangle rectangle{&vec1, &vec2};

    // Act
    ASSERT_EQ(rectangle.info(), "Rectangle (Vector ((-5.00, 9.00), (3.00, 4.00)), Vector ((3.00, 4.00), (3.00, 9.00)))");
}
