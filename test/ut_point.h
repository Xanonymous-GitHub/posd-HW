#include "../src/point.h"

TEST(PointTest, XYShouldCorrectlySet) {
    // Arrange
    const auto p = Point{1, -2};

    // Act
    EXPECT_EQ(p.x(), 1);
    EXPECT_EQ(p.y(), -2);
}

TEST(PointTest, InfoShouldReturnCorrectString) {
    // Arrange
    const auto p = Point{1, -2};

    // Act
    EXPECT_EQ(p.info(), "(1.00, -2.00)");
}

TEST(PointTest, EqualOperatorShouldReturnTrueWhenSame) {
    // Arrange
    const auto p1 = Point{1, -2};
    const auto p2 = Point{1, -2};

    // Act
    EXPECT_TRUE(p1 == p2);
}
