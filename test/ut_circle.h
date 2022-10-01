#include "../src/circle.h"

class CircleTest : public ::testing::Test {
protected:
    CircleTest() : vec{TwoDimensionalVector(&_a, &_b)} {}
    const double DEVIATION = 0.0001;
    const TwoDimensionalVector vec;
    const Point _a{-5, 9};
    const Point _b{3, 4};
};

TEST_F(CircleTest, ShouldCorrectlySetRadius) {
    // Arrange
    const Circle circle{&vec};

    // Expect
    EXPECT_EQ(circle.radius(), 9.433981132056603);
}

TEST_F(CircleTest, ShouldCorrectlyCalculateArea) {
    // Arrange
    const Circle circle{&vec};

    // Expect
    EXPECT_NEAR(circle.area(), 279.60174616949155, DEVIATION);
}

TEST_F(CircleTest, ShouldCorrectlyCalculatePerimeter) {
    // Arrange
    const Circle circle{&vec};

    // Expect
    EXPECT_NEAR(circle.perimeter(), 59.275451637147491, DEVIATION);
}

TEST_F(CircleTest, ShouldCorrectlyPrintInfo) {
    // Arrange
    const Circle circle{&vec};

    // Expect
    EXPECT_EQ(circle.info(), "Circle (Vector ((-5.00, 9.00), (3.00, 4.00)))");
}
