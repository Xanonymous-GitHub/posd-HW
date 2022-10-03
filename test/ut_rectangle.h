#include "../src/rectangle.h"

class RectangleTest : public ::testing::Test {
private:
    const Point _a{0, 0};
    const Point _b{4, 0};
    const Point _c{0, 3};
    const TwoDimensionalVector vec1_{&_a, &_b};
    const TwoDimensionalVector vec2_{&_a, &_c};

protected:
    RectangleTest() : rectangle_{&vec1_, &vec2_} {}
    const double DEVIATION = 0.0001;
    const Rectangle rectangle_;
};

TEST_F(RectangleTest, ShouldCorrectlySetLengthAndWidth) {
    // Expect
    EXPECT_EQ(rectangle_.length(), 4);
    EXPECT_EQ(rectangle_.width(), 3);
}

TEST_F(RectangleTest, ShouldCorrectlyCalculateArea) {
    // Expect
    EXPECT_NEAR(rectangle_.area(), 12, DEVIATION);
}

TEST_F(RectangleTest, ShouldCorrectlyCalculatePerimeter) {
    // Expect
    EXPECT_NEAR(rectangle_.perimeter(), 14, DEVIATION);
}

TEST_F(RectangleTest, ShouldCorrectlyPrintInfo) {
    // Expect
    EXPECT_EQ(rectangle_.info(), "Rectangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
}

TEST_F(RectangleTest, IllegalRectangle) {
    // Arrange
    const Point o{0, 0}, o_1{3, 0}, o_2{-3, 0};
    const Point k{1, 1}, k_1{4, 1}, k_2{-4, 1};
    const Point l{0, 2}, l_1{5, 2}, l_2{-5, 2};

    const TwoDimensionalVector vec1{&o, &o_1}, vec2{&o, &o_2}, vec3{&k, &k_1}, vec4{&k, &k_2}, vec5{&k_1, &k_2}, vec6{&o, &l};

    // Expect
    EXPECT_ANY_THROW(Rectangle(&vec1, &vec2));
    EXPECT_ANY_THROW(Rectangle(&vec3, &vec1));
    EXPECT_ANY_THROW(Rectangle(&vec5, &vec6));
}

TEST_F(RectangleTest, ShouldCreateNullIteratorWhenCallCreateBfsIterator) {
    // Act
    const auto it = rectangle_.createBFSIterator();

    // Expect
    EXPECT_THROW({ it->first(); }, Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(it->isDone());

    delete it;
}

TEST_F(RectangleTest, ShouldCreateNullIteratorWhenCallCreateDfsIterator) {
    // Act
    const auto it = rectangle_.createDFSIterator();

    // Expect
    EXPECT_THROW({ it->first(); }, Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(it->isDone());

    delete it;
}
