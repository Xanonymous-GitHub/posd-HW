#include "../../src/visitor/illegal_node_checker.h"

class IllegalNodeCheckerTest : public ::testing::Test {
private:
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

protected:
    const double DEVIATION = 0.0001;
    Circle circle1_{&circle1_vector_};
    Circle circle2_{&circle2_vector_};
    Rectangle rectangle1_{&rectangle1_left_vector_, &rectangle1_right_vector_};
    Rectangle rectangle2_{&rectangle2_left_vector_, &rectangle2_right_vector_};
    Rectangle rectangle3_{&rectangle3_left_vector_, &rectangle3_right_vector_};
    Triangle triangle_{&triangle_left_vector_, &triangle_right_vector_};
};

/**
 * Oh ! Yea! Let's DON't use const anymore!
 * Because the TA not want us to use const!
 */

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitCircleAndFindItIsLlegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    // Act
    circle1_.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_FALSE(result);
}

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitTriangleAndFindItIsLlegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    // Act
    triangle_.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_FALSE(result);
}

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitRectangleAndFindItIsLlegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    // Act
    rectangle1_.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_FALSE(result);
}

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitNoChildCompoundShapeAndFindItIsIllegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    auto givenIllegalCompoundShape = CompoundShape{};

    // Act
    givenIllegalCompoundShape.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_TRUE(result);
}

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitOneCompoundChildCompoundShapeAndFindItIsIllegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    CompoundShape compound_shape1_{};

    Shape *content_of_compound_shape2_[1] = {&compound_shape1_};
    CompoundShape compound_shape2_{content_of_compound_shape2_, 1};

    // Act
    compound_shape2_.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_TRUE(result);
}

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitTwoLeafChildrenCompoundShapeAndFindItIsNOTIllegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    Shape *content_of_compound_shape2_[2] = {&circle1_, &rectangle1_};
    CompoundShape compound_shape2_{content_of_compound_shape2_, 2};

    // Act
    compound_shape2_.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_FALSE(result);
}

TEST_F(IllegalNodeCheckerTest, shouldCorrectlyVisitOneCompoundChildOneLeafChildCompoundShapeAndFindItIsNOTIllegal) {
    // Arrange
    IllegalNodeChecker illegalNodeChecker{};

    CompoundShape compound_shape1_{};

    Shape *content_of_compound_shape2_[2] = {&compound_shape1_, &circle1_};
    CompoundShape compound_shape2_{content_of_compound_shape2_, 2};

    // Act
    compound_shape2_.accept(&illegalNodeChecker);

    // Expect
    const auto result = illegalNodeChecker.isIllegal();
    EXPECT_FALSE(result);
}
