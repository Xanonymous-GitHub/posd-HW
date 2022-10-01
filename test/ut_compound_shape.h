#include "../src/compound_shape.h"

class CompoundShapeTest : public ::testing::Test {
private:
    /**
     * @brief Points that make up a vector for a `Circle`.
     */
    const Point circle_vector_start_{0, 0};
    const Point circle_vector_end_{4, 0};

    // The vector for creating a `Circle`.
    const TwoDimensionalVector circle_vector_{&circle_vector_start_, &circle_vector_end_};

    /**
     * @brief Points that make up a vector for a `Triangle`.
     */
    const Point triangle_vector_start_{0, 0};
    const Point triangle_left_vector_end_{4, 0};
    const Point triangle_right_vector_end_{0, 3};

    // The vectors for creating a `Triangle`.
    const TwoDimensionalVector triangle_left_vector_{&triangle_vector_start_, &triangle_left_vector_end_};
    const TwoDimensionalVector triangle_right_vector_{&triangle_vector_start_, &triangle_right_vector_end_};

    /**
     * @brief Points that make up a vector for a `Rectangle`.
     */
    const Point rectangle_vector_start_{0, 0};
    const Point rectangle_left_vector_end_{3, 0};
    const Point rectangle_right_vector_end_{0, 5};

    // The vectors for creating a `Rectangle`.
    const TwoDimensionalVector rectangle_left_vector_{&rectangle_vector_start_, &rectangle_left_vector_end_};
    const TwoDimensionalVector rectangle_right_vector_{&rectangle_vector_start_, &rectangle_right_vector_end_};

protected:
    const double DEVIATION = 0.0001;
    const Circle circle_{&circle_vector_};
    const Rectangle rectangle_{&rectangle_left_vector_, &rectangle_right_vector_};
    const Triangle triangle_{&triangle_left_vector_, &triangle_right_vector_};
};

class CompoundShapeTestWithoutNesting : public CompoundShapeTest {
protected:
    /**
     * compound_shape_
     * |
     * |--- circle_
     * |-- rectangle_
     * |-- triangle_
     */
    const CompoundShape compound_shape_{circle_, rectangle_, triangle_};
};

class CompoundShapeTestWithNesting : public CompoundShapeTestWithoutNesting {
protected:
    /**
     * compound_shape_n1_
     * |
     * |--- circle_
     * |-- rectangle_
     * |-- triangle_
     * |--- compound_shape_
     * |   |
     * |   |--- circle_
     * |   |-- rectangle_
     * |   |-- triangle_
     */
    const CompoundShape compound_shape_n1_{circle_, rectangle_, triangle_, compound_shape_};
};

class CompoundShapeTestWithMultipleNesting : public CompoundShapeTestWithNesting {
protected:
    /**
     * compound_shape_n2_
     * |
     * |--- circle_
     * |-- rectangle_
     * |-- triangle_
     * |--- compound_shape_n1_
     * |   |
     * |   |--- circle_
     * |   |-- rectangle_
     * |   |-- triangle_
     * |   |--- compound_shape_
     * |   |   |
     * |   |   |--- circle_
     * |   |   |-- rectangle_
     * |   |   |-- triangle_
     */
    const CompoundShape compound_shape_n2_{circle_, rectangle_, triangle_, compound_shape_n1_};
};

TEST_F(CompoundShapeTestWithoutNesting, AreaShouldBeCorrect) {
    // Arrange
    const double expected_area = (4 * 4 * M_PI) + (3 * 5) + (4 * 3 / 2);

    // Act
    const double actual_area = compound_shape_.area();

    // Expect
    EXPECT_NEAR(actual_area, expected_area, DEVIATION);
}

TEST_F(CompoundShapeTestWithoutNesting, PerimeterShouldBeCorrect) {
    // Arrange
    const double expected_perimeter = (2 * 4 * M_PI) + (2 * (3 + 5)) + (4 + 3 + 5);

    // Act
    const double actual_perimeter = compound_shape_.perimeter();

    // Expect
    EXPECT_NEAR(actual_perimeter, expected_perimeter, DEVIATION);
}

TEST_F(CompoundShapeTestWithoutNesting, InfoShouldBeCorrect) {
    // Arrange
    const std::string expected_info =
        // clang-format off
        "CompoundShape ("
            "Circle ("
                "Vector ((0.00, 0.00), (4.00, 0.00))"
            "), "
            "Rectangle ("
                "Vector ((0.00, 0.00), (3.00, 0.00)), "
                "Vector ((0.00, 0.00), (0.00, 5.00))"
            "), "
            "Triangle ("
                "Vector ((0.00, 0.00), (4.00, 0.00)), "
                "Vector ((0.00, 0.00), (0.00, 3.00))"
            ")"
        ")";
    // clang-format on

    // Act
    const std::string actual_info = compound_shape_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}
