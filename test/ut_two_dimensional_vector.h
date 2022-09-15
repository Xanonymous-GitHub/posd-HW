#include "../src/two_dimensional_vector.h"

class TwoDimensionalVectorTest : public ::testing::Test {
protected:
    TwoDimensionalVectorTest() : vec{TwoDimensionalVector(&_a, &_b)} {}
    const double DEVIATION = 0.0001;
    const TwoDimensionalVector vec;
    const Point _a{-5, 9};
    const Point _b{3, 4};
};

TEST_F(TwoDimensionalVectorTest, ShouldCorrectlySetBeginAndEnd) {
    ASSERT_EQ(vec.a(), &_a);
    ASSERT_EQ(vec.b(), &_b);
}

TEST_F(TwoDimensionalVectorTest, ShouldCorrectlyCalculateLength) {
    ASSERT_NEAR(vec.length(), 9.433981132056603, DEVIATION);
}

TEST_F(TwoDimensionalVectorTest, ShouldCorrectlyCalculateDotProduct) {
    // Arrange
    const Point c{0, 0};
    const Point d{1, 1};
    const TwoDimensionalVector vec2{&c, &d};

    // Act
    ASSERT_NEAR(vec.dot(&vec2), 3, DEVIATION);
}

TEST_F(TwoDimensionalVectorTest, ShouldCorrectlyCalculateCrossProduct) {
    // Arrange
    const Point c{0, 0};
    const Point d{1, 1};
    const TwoDimensionalVector vec2{&c, &d};

    // Act
    ASSERT_NEAR(vec.cross(&vec2), 13, DEVIATION);
}

TEST_F(TwoDimensionalVectorTest, ShouldCorrectlyPrintInfo) {
    ASSERT_EQ(vec.info(), "Vector ((-5.00, 9.00), (3.00, 4.00))");
}
