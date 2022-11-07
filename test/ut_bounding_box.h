#include "../src/bounding_box.h"

class BoundingBoxTest : public ::testing::Test {
protected:
    /**
     * @brief Points that make up a vector for a `Circle`.
     */
    const Point circle1_vector_start_{2, 2};
    const Point circle1_vector_end_{8, 2};

    // The vector for creating a `Circle`.
    const TwoDimensionalVector circle1_vector_{&circle1_vector_start_, &circle1_vector_end_};

    /**
     * @brief Points that make up a vector for a `Circle`.
     */
    const Point circle2_vector_start_{16, 14};
    const Point circle2_vector_end_{20, 14};

    // The vector for creating a `Circle`.
    const TwoDimensionalVector circle2_vector_{&circle2_vector_start_, &circle2_vector_end_};

    /**
     * @brief Points that make up a vector for a `Triangle`.
     */
    const Point triangle_vector_start_{4, 6};
    const Point triangle_left_vector_end_{6, 10};
    const Point triangle_right_vector_end_{8, 6};

    // The vectors for creating a `Triangle`.
    const TwoDimensionalVector triangle_left_vector_{&triangle_vector_start_, &triangle_left_vector_end_};
    const TwoDimensionalVector triangle_right_vector_{&triangle_vector_start_, &triangle_right_vector_end_};

    /**
     * @brief Points that make up a vector for a `Rectangle`.
     */
    const Point rectangle1_vector_start_{14, 8};
    const Point rectangle1_left_vector_end_{14, 12};
    const Point rectangle1_right_vector_end_{16, 8};

    // The vectors for creating a `Rectangle`.
    const TwoDimensionalVector rectangle1_left_vector_{&rectangle1_vector_start_, &rectangle1_left_vector_end_};
    const TwoDimensionalVector rectangle1_right_vector_{&rectangle1_vector_start_, &rectangle1_right_vector_end_};

    /**
     * @brief Points that make up a vector for a `Rectangle`.
     */
    const Point rectangle2_vector_start_{0, 4};
    const Point rectangle2_left_vector_end_{6, 4};
    const Point rectangle2_right_vector_end_{0, 8};

    // The vectors for creating a `Rectangle`.
    const TwoDimensionalVector rectangle2_left_vector_{&rectangle2_vector_start_, &rectangle2_left_vector_end_};
    const TwoDimensionalVector rectangle2_right_vector_{&rectangle2_vector_start_, &rectangle2_right_vector_end_};

    /**
     * @brief Points that make up a vector for a `Rectangle`.
     */
    const Point rectangle3_vector_start_{4, 6};
    const Point rectangle3_left_vector_end_{6, 6};
    const Point rectangle3_right_vector_end_{4, 8};

    // The vectors for creating a `Rectangle`.
    const TwoDimensionalVector rectangle3_left_vector_{&rectangle3_vector_start_, &rectangle3_left_vector_end_};
    const TwoDimensionalVector rectangle3_right_vector_{&rectangle3_vector_start_, &rectangle3_right_vector_end_};

    const double DEVIATION = 0.0001;
    Point happyPoint1{6, 10};
    Point happyPoint2{8, 6};
    Point happyPoint3{4, 5};
    Circle circle1_{&circle1_vector_};
    Circle circle2_{&circle2_vector_};
    Rectangle rectangle1_{&rectangle1_left_vector_, &rectangle1_right_vector_};
    Rectangle rectangle2_{&rectangle2_left_vector_, &rectangle2_right_vector_};
    Rectangle rectangle3_{&rectangle3_left_vector_, &rectangle3_right_vector_};
    Triangle triangle_{&triangle_left_vector_, &triangle_right_vector_};
};

TEST_F(BoundingBoxTest, shouldCorrectlyFindTopRightPoint) {
    // Arrange
    const auto pointSet = std::set<const Point *>{&happyPoint1, &happyPoint2, &happyPoint3};
    const auto boundingBox = BoundingBox(pointSet);

    // Act
    const auto topRightPoint = boundingBox.max();

    // Expect
    EXPECT_EQ(topRightPoint->x(), 8);
    EXPECT_EQ(topRightPoint->y(), 10);
}

TEST_F(BoundingBoxTest, shouldCorrectlyFindBottomLeftPoint) {
    // Arrange
    const auto pointSet = std::set<const Point *>{&happyPoint1, &happyPoint2, &happyPoint3};
    const auto boundingBox = BoundingBox(pointSet);

    // Act
    const auto bottomLeftPoint = boundingBox.min();

    // Expect
    EXPECT_EQ(bottomLeftPoint->x(), 4);
    EXPECT_EQ(bottomLeftPoint->y(), 5);
}

TEST_F(BoundingBoxTest, shouldCorrectlyFindTopRightPointForCircle) {
    // Arrange
    const auto pointSet = circle1_.getPoints();
    const auto boundingBox = BoundingBox(pointSet);

    // Act
    const auto topRightPoint = boundingBox.max();
    const auto bottomLeftPoint = boundingBox.min();

    // Expect
    EXPECT_NEAR(topRightPoint->x(), 8, DEVIATION);
    EXPECT_NEAR(topRightPoint->y(), 8, DEVIATION);
    EXPECT_NEAR(bottomLeftPoint->x(), -4, DEVIATION);
    EXPECT_NEAR(bottomLeftPoint->y(), -4, DEVIATION);
}

TEST_F(BoundingBoxTest, shouldCorrectlyFindTopRightPointForRectangle) {
    // Arrange
    const auto pointSet = rectangle1_.getPoints();
    const auto boundingBox = BoundingBox(pointSet);

    // Act
    const auto topRightPoint = boundingBox.max();
    const auto bottomLeftPoint = boundingBox.min();

    // Expect
    EXPECT_NEAR(topRightPoint->x(), 16, DEVIATION);
    EXPECT_NEAR(topRightPoint->y(), 12, DEVIATION);
    EXPECT_NEAR(bottomLeftPoint->x(), 14, DEVIATION);
    EXPECT_NEAR(bottomLeftPoint->y(), 8, DEVIATION);
}

TEST_F(BoundingBoxTest, shouldCorrectlyFindTopRightPointForTriangle) {
    // Arrange
    const auto pointSet = triangle_.getPoints();
    const auto boundingBox = BoundingBox(pointSet);

    // Act
    const auto topRightPoint = boundingBox.max();
    const auto bottomLeftPoint = boundingBox.min();

    // Expect
    EXPECT_NEAR(topRightPoint->x(), 8, DEVIATION);
    EXPECT_NEAR(topRightPoint->y(), 10, DEVIATION);
    EXPECT_NEAR(bottomLeftPoint->x(), 4, DEVIATION);
    EXPECT_NEAR(bottomLeftPoint->y(), 6, DEVIATION);
}

TEST_F(BoundingBoxTest, shouldBeRecognizedAsCollideOfTwoCollideShapes1) {
    // Arrange
    const auto pointSet1 = rectangle1_.getPoints();
    const auto pointSet2 = circle2_.getPoints();
    const auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto isCollide = boundingBox2.collide(&boundingBox1);

    // Expect
    EXPECT_TRUE(isCollide);
}

TEST_F(BoundingBoxTest, shouldBeRecognizedAsCollideOfTwoCollideShapes2) {
    // Arrange
    const auto pointSet1 = triangle_.getPoints();
    const auto pointSet2 = circle1_.getPoints();
    const auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto isCollide = boundingBox2.collide(&boundingBox1);

    // Expect
    EXPECT_TRUE(isCollide);
}

TEST_F(BoundingBoxTest, shouldBeRecognizedAsCollideOfTwoCollideShapes3) {
    // Arrange
    const auto pointSet1 = rectangle2_.getPoints();
    const auto pointSet2 = rectangle3_.getPoints();
    const auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto isCollide = boundingBox2.collide(&boundingBox1);

    // Expect
    EXPECT_TRUE(isCollide);
}

TEST_F(BoundingBoxTest, shouldBeRecognizedAsNOTCollideOfTwoNONCollideShapes1) {
    // Arrange
    const auto pointSet1 = circle1_.getPoints();
    const auto pointSet2 = circle2_.getPoints();
    const auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto isCollide = boundingBox2.collide(&boundingBox1);

    // Expect
    EXPECT_FALSE(isCollide);
}

TEST_F(BoundingBoxTest, shouldBeRecognizedAsNOTCollideOfTwoNONCollideShapes2) {
    // Arrange
    const auto pointSet1 = circle1_.getPoints();
    const auto pointSet2 = rectangle1_.getPoints();
    const auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto isCollide = boundingBox2.collide(&boundingBox1);

    // Expect
    EXPECT_FALSE(isCollide);
}

TEST_F(BoundingBoxTest, shouldBeRecognizedAsNOTCollideOfTwoNONCollideShapes3) {
    // Arrange
    const auto pointSet1 = triangle_.getPoints();
    const auto pointSet2 = circle2_.getPoints();
    const auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto isCollide = boundingBox2.collide(&boundingBox1);

    // Expect
    EXPECT_FALSE(isCollide);
}

TEST_F(BoundingBoxTest, ShouldGetCorrectDistance) {
    // Arrange
    const auto pointSet1 = triangle_.getPoints();
    const auto pointSet2 = circle2_.getPoints();
    auto boundingBox1 = BoundingBox(pointSet1);
    auto boundingBox2 = BoundingBox(pointSet2);

    // Act
    const auto dis = boundingBox2.distance(&boundingBox1);

    // Expect
    // std::cout<<dis<<std::endl;
    EXPECT_NEAR(dis, 23.3665, DEVIATION);
}
