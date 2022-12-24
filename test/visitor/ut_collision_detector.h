#include "../../src/visitor/collision_detector.h"

class CollisionDetectorTest : public ::testing::Test {
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
    Circle circle1_{circle1_vector_};
    Circle circle2_{circle2_vector_};
    Rectangle rectangle1_{rectangle1_left_vector_, rectangle1_right_vector_};
    Rectangle rectangle2_{rectangle2_left_vector_, rectangle2_right_vector_};
    Rectangle rectangle3_{rectangle3_left_vector_, rectangle3_right_vector_};
    Triangle triangle_{triangle_left_vector_, triangle_right_vector_};
};

/**
 * Oh ! Yea! Let's DON't use const anymore!
 * Because the TA not want us to use const!
 */

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitCircleAndFindItCollidesWithAShape) {
    // Arrange
    CollisionDetector collisionDetector{&triangle_};

    // Act
    circle1_.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), &circle1_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitCircleAndFindItNOTCollidesWithAnyShape) {
    // Arrange
    CollisionDetector collisionDetector{&triangle_};

    // Act
    circle2_.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_FALSE(std::find(result.cbegin(), result.cend(), &circle2_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitRectangleAndFindItCollidesWithAShape) {
    // Arrange
    CollisionDetector collisionDetector{&circle2_};

    // Act
    rectangle1_.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), &rectangle1_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitRectangleAndFindItNOTCollidesWithAnyShape) {
    // Arrange
    CollisionDetector collisionDetector{&circle1_};

    // Act
    rectangle1_.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_FALSE(std::find(result.cbegin(), result.cend(), &rectangle1_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitTriangleAndFindItCollidesWithAShape) {
    // Arrange
    CollisionDetector collisionDetector{&circle1_};

    // Act
    triangle_.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), &triangle_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitTriangleAndFindItNOTCollidesWithAnyShape) {
    // Arrange
    CollisionDetector collisionDetector{&circle2_};

    // Act
    triangle_.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_FALSE(std::find(result.cbegin(), result.cend(), &triangle_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitCompoundShapeAndFindItsChildrenCollidesWithAShape) {
    // Arrange
    auto circle1_ = new Circle{circle1_vector_};
    Circle circle2_{circle2_vector_};
    Rectangle rectangle1_{rectangle1_left_vector_, rectangle1_right_vector_};
    auto rectangle2_ = new Rectangle{rectangle2_left_vector_, rectangle2_right_vector_};
    Rectangle rectangle3_{rectangle3_left_vector_, rectangle3_right_vector_};
    auto triangle_ = new Triangle{triangle_left_vector_, triangle_right_vector_};
    CollisionDetector collisionDetector{&rectangle3_};
    Shape *content_of_compound_shape_[3] = {circle1_, rectangle2_, triangle_};
    CompoundShape compoundShape{content_of_compound_shape_, 3};

    // Act
    compoundShape.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), circle1_) != result.cend());
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), rectangle2_) != result.cend());
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), triangle_) != result.cend());
}

TEST_F(CollisionDetectorTest, shouldCorrectlyVisitCompoundShapeAndFindSomeOfItsChildrenWhichHasAnotherCompoundShapeCollidesWithAShape) {
    // Arrange
    auto circle1_ = new Circle{circle1_vector_};
    auto circle2_ = new Circle{circle2_vector_};
    auto rectangle1_ = new Rectangle{rectangle1_left_vector_, rectangle1_right_vector_};
    auto rectangle2_ = new Rectangle{rectangle2_left_vector_, rectangle2_right_vector_};
    Rectangle rectangle3_{rectangle3_left_vector_, rectangle3_right_vector_};
    CollisionDetector collisionDetector{&rectangle3_};
    Shape *content_of_compound_shape1_[2] = {circle2_, rectangle1_};
    auto compoundShape1 = new CompoundShape{content_of_compound_shape1_, 2};

    Shape *content_of_compound_shape2_[3] = {circle1_, rectangle2_, compoundShape1};
    CompoundShape compoundShape2{content_of_compound_shape2_, 3};

    // Act
    compoundShape2.accept(&collisionDetector);

    // Expect
    const auto result = collisionDetector.collidedShapes();
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), circle1_) != result.cend());
    EXPECT_TRUE(std::find(result.cbegin(), result.cend(), rectangle2_) != result.cend());
}
