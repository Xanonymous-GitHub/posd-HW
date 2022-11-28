#include "../../src/builder/shape_builder.h"

class ShapeBuilderTest : public ::testing::Test {
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
    Circle circle1_{&circle1_vector_};
    Circle circle2_{&circle2_vector_};
    Rectangle rectangle1_{&rectangle1_left_vector_, &rectangle1_right_vector_};
    Rectangle rectangle2_{&rectangle2_left_vector_, &rectangle2_right_vector_};
    Rectangle rectangle3_{&rectangle3_left_vector_, &rectangle3_right_vector_};
    Triangle triangle_{&triangle_left_vector_, &triangle_right_vector_};

    ShapeBuilder shape_builder_{};

    template <typename Container>
    void safeDelete_(Container &container) {
        for (auto &element : container) {
            delete element;
        }
    }
};

TEST_F(ShapeBuilderTest, ShouldCorrectlyBuildCircle) {
    // Act
    shape_builder_.buildCircle(&circle1_vector_start_, &circle1_vector_end_);
    const auto result = shape_builder_.getResult();

    // Expect
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 2.00), (8.00, 2.00)))");

    // Clean up
    safeDelete_(result);
}

TEST_F(ShapeBuilderTest, ShouldCorrectlyBuildTriangle) {
    // Act
    shape_builder_.buildTriangle(&triangle_vector_start_, &triangle_left_vector_end_, &triangle_right_vector_end_);
    const auto result = shape_builder_.getResult();

    // Expect
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");

    // Clean up
    safeDelete_(result);
}

TEST_F(ShapeBuilderTest, ShouldCorrectlyBuildRectangle) {
    // Act
    shape_builder_.buildRectangle(&rectangle1_vector_start_, &rectangle1_left_vector_end_, &rectangle1_right_vector_end_);
    const auto result = shape_builder_.getResult();

    // Expect
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result.at(0)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");

    // Clean up
    safeDelete_(result);
}

TEST_F(ShapeBuilderTest, ShouldCorrectlyBuildMultipleSimpleShapes) {
    // Act
    shape_builder_.buildCircle(&circle1_vector_start_, &circle1_vector_end_);
    shape_builder_.buildTriangle(&triangle_vector_start_, &triangle_left_vector_end_, &triangle_right_vector_end_);
    shape_builder_.buildRectangle(&rectangle1_vector_start_, &rectangle1_left_vector_end_, &rectangle1_right_vector_end_);
    const auto result = shape_builder_.getResult();

    // Expect
    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 2.00), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(2)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");

    // Clean up
    safeDelete_(result);
}

TEST_F(ShapeBuilderTest, ShouldCorrectlyBuildShapesWithSimpleCompound) {
    // Arrange
    const std::string expected_info =
        // clang-format off
        "CompoundShape ("
            "Circle ("
                "Vector ((16.00, 14.00), (20.00, 14.00))"
            "), "
            "Rectangle ("
                "Vector ((0.00, 4.00), (6.00, 4.00)), "
                "Vector ((0.00, 4.00), (0.00, 8.00))"
            ")"
        ")";
    // clang-format on

    // Act
    shape_builder_.buildCircle(&circle1_vector_start_, &circle1_vector_end_);
    shape_builder_.buildTriangle(&triangle_vector_start_, &triangle_left_vector_end_, &triangle_right_vector_end_);
    shape_builder_.buildRectangle(&rectangle1_vector_start_, &rectangle1_left_vector_end_, &rectangle1_right_vector_end_);
    shape_builder_.buildCompoundShape();
    shape_builder_.buildCircle(&circle2_vector_start_, &circle2_vector_end_);
    shape_builder_.buildRectangle(&rectangle2_vector_start_, &rectangle2_left_vector_end_, &rectangle2_right_vector_end_);
    shape_builder_.buildCompoundEnd();
    const auto result = shape_builder_.getResult();

    // Expect
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 2.00), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(2)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
    EXPECT_EQ(result.at(3)->info(), expected_info);

    // Clean up
    safeDelete_(result);
}

TEST_F(ShapeBuilderTest, ShouldCorrectlyBuildShapesWithMultipleCompounds) {
    // Arrange
    const std::string expected_info =
        // clang-format off
        "CompoundShape ("
            "CompoundShape ("
                "Circle ("
                    "Vector ((16.00, 14.00), (20.00, 14.00))"
                "), "
                "Rectangle ("
                    "Vector ((0.00, 4.00), (6.00, 4.00)), "
                    "Vector ((0.00, 4.00), (0.00, 8.00))"
                ")"
            "), "
            "Circle ("
                "Vector ((2.00, 2.00), (8.00, 2.00))"
            ")"
        ")";
    // clang-format on

    // Act
    shape_builder_.buildCircle(&circle1_vector_start_, &circle1_vector_end_);
    shape_builder_.buildTriangle(&triangle_vector_start_, &triangle_left_vector_end_, &triangle_right_vector_end_);
    shape_builder_.buildRectangle(&rectangle1_vector_start_, &rectangle1_left_vector_end_, &rectangle1_right_vector_end_);
    shape_builder_.buildCompoundShape();
    shape_builder_.buildCompoundShape();
    shape_builder_.buildCircle(&circle2_vector_start_, &circle2_vector_end_);
    shape_builder_.buildRectangle(&rectangle2_vector_start_, &rectangle2_left_vector_end_, &rectangle2_right_vector_end_);
    shape_builder_.buildCompoundEnd();
    shape_builder_.buildCircle(&circle1_vector_start_, &circle1_vector_end_);
    shape_builder_.buildCompoundEnd();
    const auto result = shape_builder_.getResult();

    // Expect
    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result.at(0)->info(), "Circle (Vector ((2.00, 2.00), (8.00, 2.00)))");
    EXPECT_EQ(result.at(1)->info(), "Triangle (Vector ((4.00, 6.00), (6.00, 10.00)), Vector ((4.00, 6.00), (8.00, 6.00)))");
    EXPECT_EQ(result.at(2)->info(), "Rectangle (Vector ((14.00, 8.00), (14.00, 12.00)), Vector ((14.00, 8.00), (16.00, 8.00)))");
    EXPECT_EQ(result.at(3)->info(), expected_info);

    // Clean up
    safeDelete_(result);
}
