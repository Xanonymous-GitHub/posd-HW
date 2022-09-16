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

TEST_F(TriangleTest, IllegalTriangle) {
    // Arrange
    const Point o{0, 0}, o_1{3, 0}, o_2{-3, 0};
    const Point k{1, 1}, k_1{4, 1}, k_2{-4, 1};
    const Point l{0, 2}, l_1{5, 2}, l_2{-5, 2};

    const TwoDimensionalVector vec1{&o, &o_1}, vec2{&o, &o_2}, vec3{&k, &k_1}, vec4{&k, &k_2}, vec5{&k_1, &k_2}, vec6{&o, &l};

    // Act
    ASSERT_ANY_THROW(Triangle(&vec1, &vec2));
    ASSERT_ANY_THROW(Triangle(&vec3, &vec1));
    ASSERT_ANY_THROW(Triangle(&vec5, &vec6));
}
