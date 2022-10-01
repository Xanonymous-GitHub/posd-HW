#include "../src/point.h"

TEST(PointTest, XYShouldCorrectlySet) {
    // Arrange
    const Point p{1, -2};

    // Expect
    EXPECT_EQ(p.x(), 1);
    EXPECT_EQ(p.y(), -2);
}

TEST(PointTest, InfoShouldReturnCorrectString) {
    // Arrange
    const Point p{1, -2};

    // Expect
    EXPECT_EQ(p.info(), "(1.00, -2.00)");
}

TEST(PointTest, EqualOperatorShouldReturnTrueWhenSame) {
    // Arrange
    const Point p1{1, -2};
    const Point p2{1, -2};

    // Expect
    EXPECT_TRUE(p1 == p2);
}

TEST(PointTest, EqualOperatorShouldReturnTrueWhenSameReference) {
    // Arrange
    const Point p1{1, -2};

    // Expect
    EXPECT_TRUE(p1 == p1);
}

TEST(PointTest, EqualOperatorShouldReturnFalseWhenDifferent) {
    // Arrange
    const Point p1{1, -2};
    const Point p2{2, -1};

    // Expect
    EXPECT_FALSE(p1 == p2);
}

TEST(PointTest, EqualOperatorShouldReturnFalseWhenDifferentReference) {
    // Arrange
    const Point p1{1, -2};
    const Point p2{2, -1};

    // Expect
    EXPECT_FALSE(p1 == p2);
}
