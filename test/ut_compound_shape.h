#include "../src/compound_shape.h"

class CompoundShapeTest : public ::testing::Test {
private:
    /**
     * @brief Points that make up a vector for a `Circle`.
     */
    const Point circle_vector_start_{0, 0};
    const Point circle_vector_end_{4, 0};

    // The vector for creating a `Circle`.
    const TwoDimensionalVector circle_vector_{circle_vector_start_, circle_vector_end_};

    /**
     * @brief Points that make up a vector for a `Triangle`.
     */
    const Point triangle_vector_start_{0, 0};
    const Point triangle_left_vector_end_{4, 0};
    const Point triangle_right_vector_end_{0, 3};

    // The vectors for creating a `Triangle`.
    const TwoDimensionalVector triangle_left_vector_{triangle_vector_start_, triangle_left_vector_end_};
    const TwoDimensionalVector triangle_right_vector_{triangle_vector_start_, triangle_right_vector_end_};

    /**
     * @brief Points that make up a vector for a `Rectangle`.
     */
    const Point rectangle_vector_start_{0, 0};
    const Point rectangle_left_vector_end_{3, 0};
    const Point rectangle_right_vector_end_{0, 5};

    // The vectors for creating a `Rectangle`.
    const TwoDimensionalVector rectangle_left_vector_{rectangle_vector_start_, rectangle_left_vector_end_};
    const TwoDimensionalVector rectangle_right_vector_{rectangle_vector_start_, rectangle_right_vector_end_};

protected:
    const double DEVIATION = 0.0001;
    Circle circle_{circle_vector_};
    Rectangle rectangle_{rectangle_left_vector_, rectangle_right_vector_};
    Triangle triangle_{triangle_left_vector_, triangle_right_vector_};
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
    Shape *content_of_compound_shape_[3] = {&circle_, &rectangle_, &triangle_};
    CompoundShape compound_shape_{content_of_compound_shape_, 3};
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
    Shape *content_of_compound_shape_n1_[4] = {&circle_, &rectangle_, &triangle_, &compound_shape_};
    CompoundShape compound_shape_n1_{content_of_compound_shape_n1_, 4};
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
    Shape *content_of_compound_shape_n2_[4] = {&circle_, &rectangle_, &triangle_, &compound_shape_n1_};
    CompoundShape compound_shape_n2_{content_of_compound_shape_n2_, 4};
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

TEST_F(CompoundShapeTestWithoutNesting, ShouldCorrectlyAddShape) {
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
            "), "
            "Circle ("
                "Vector ((0.00, 0.00), (4.00, 0.00))"
            ")"
        ")";
    // clang-format on

    // Act
    compound_shape_.addShape(&circle_);
    const std::string actual_info = compound_shape_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithoutNesting, ShouldCorrectlyDeleteShape) {
    // Arrange
    const std::string expected_info =
        // clang-format off
        "CompoundShape ("
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
    compound_shape_.deleteShape(&circle_);
    const std::string actual_info = compound_shape_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithNesting, AreaShouldBeCorrect) {
    // Arrange
    const double area_of_lv1_circle = 4 * 4 * M_PI;
    const double area_of_lv1_rectangle = 3 * 5;
    const double area_of_lv1_triangle = 4 * 3 / 2;
    const double area_of_lv1_compound_shape = (4 * 4 * M_PI) + (3 * 5) + (4 * 3 / 2);
    const double expected_area = area_of_lv1_circle + area_of_lv1_rectangle + area_of_lv1_triangle + area_of_lv1_compound_shape;

    // Act
    const double actual_area = compound_shape_n1_.area();

    // Expect
    EXPECT_NEAR(actual_area, expected_area, DEVIATION);
}

TEST_F(CompoundShapeTestWithNesting, PerimeterShouldBeCorrect) {
    // Arrange
    const double perimeter_of_lv1_circle = 2 * 4 * M_PI;
    const double perimeter_of_lv1_rectangle = 2 * (3 + 5);
    const double perimeter_of_lv1_triangle = 4 + 3 + 5;
    const double perimeter_of_lv1_compound_shape = (2 * 4 * M_PI) + (2 * (3 + 5)) + (4 + 3 + 5);
    const double expected_perimeter = perimeter_of_lv1_circle + perimeter_of_lv1_rectangle + perimeter_of_lv1_triangle + perimeter_of_lv1_compound_shape;

    // Act
    const double actual_perimeter = compound_shape_n1_.perimeter();

    // Expect
    EXPECT_NEAR(actual_perimeter, expected_perimeter, DEVIATION);
}

TEST_F(CompoundShapeTestWithNesting, InfoShouldBeCorrect) {
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
            "), "
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
            ")"
        ")";
    // clang-format on

    // Act
    const std::string actual_info = compound_shape_n1_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithNesting, ShouldCorrectlyAddShape) {
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
            "), "
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
            "), "
            "Circle ("
                "Vector ((0.00, 0.00), (4.00, 0.00))"
            ")"
        ")";
    // clang-format on

    // Act
    compound_shape_n1_.addShape(&circle_);
    const std::string actual_info = compound_shape_n1_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithNesting, ShouldCorrectlyDeleteShape) {
    // Arrange
    const std::string expected_info =
        // clang-format off
        "CompoundShape ("
            "Rectangle ("
                "Vector ((0.00, 0.00), (3.00, 0.00)), "
                "Vector ((0.00, 0.00), (0.00, 5.00))"
            "), "
            "Triangle ("
                "Vector ((0.00, 0.00), (4.00, 0.00)), "
                "Vector ((0.00, 0.00), (0.00, 3.00))"
            "), "
            "CompoundShape ("
                "Rectangle ("
                    "Vector ((0.00, 0.00), (3.00, 0.00)), "
                    "Vector ((0.00, 0.00), (0.00, 5.00))"
                "), "
                "Triangle ("
                    "Vector ((0.00, 0.00), (4.00, 0.00)), "
                    "Vector ((0.00, 0.00), (0.00, 3.00))"
                ")"
            ")"
        ")";
    // clang-format on

    // Act
    compound_shape_n1_.deleteShape(&circle_);
    const std::string actual_info = compound_shape_n1_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithMultipleNesting, AreaShouldBeCorrect) {
    // Arrange
    const double area_of_lv1_circle = M_PI * 4 * 4;
    const double area_of_lv1_rectangle = 3 * 5;
    const double area_of_lv1_triangle = 0.5 * 4 * 3;
    const double area_of_lv2_circle = M_PI * 4 * 4;
    const double area_of_lv2_rectangle = 3 * 5;
    const double area_of_lv2_triangle = 0.5 * 4 * 3;
    const double area_of_lv2_compound_shape = (M_PI * 4 * 4) + (3 * 5) + (0.5 * 4 * 3);
    const double area_of_lv1_compound_shape = area_of_lv2_circle + area_of_lv2_rectangle + area_of_lv2_triangle + area_of_lv2_compound_shape;
    const double expected_area = area_of_lv1_circle + area_of_lv1_rectangle + area_of_lv1_triangle + area_of_lv1_compound_shape;

    // Act
    const double actual_area = compound_shape_n2_.area();

    // Expect
    EXPECT_NEAR(actual_area, expected_area, DEVIATION);
}

TEST_F(CompoundShapeTestWithMultipleNesting, PerimeterShouldBeCorrect) {
    // Arrange
    const double perimeter_of_lv1_circle = 2 * M_PI * 4;
    const double perimeter_of_lv1_rectangle = 2 * (3 + 5);
    const double perimeter_of_lv1_triangle = 4 + 3 + sqrt(4 * 4 + 3 * 3);
    const double perimeter_of_lv2_circle = 2 * M_PI * 4;
    const double perimeter_of_lv2_rectangle = 2 * (3 + 5);
    const double perimeter_of_lv2_triangle = 4 + 3 + sqrt(4 * 4 + 3 * 3);
    const double perimeter_of_lv2_compound_shape = 2 * M_PI * 4 + 2 * (3 + 5) + 4 + 3 + sqrt(4 * 4 + 3 * 3);
    const double perimeter_of_lv1_compound_shape = perimeter_of_lv2_circle + perimeter_of_lv2_rectangle + perimeter_of_lv2_triangle + perimeter_of_lv2_compound_shape;
    const double expected_perimeter = perimeter_of_lv1_circle + perimeter_of_lv1_rectangle + perimeter_of_lv1_triangle + perimeter_of_lv1_compound_shape;

    // Act
    const double actual_perimeter = compound_shape_n2_.perimeter();

    // Expect
    EXPECT_NEAR(actual_perimeter, expected_perimeter, DEVIATION);
}

TEST_F(CompoundShapeTestWithMultipleNesting, InfoShouldBeCorrect) {
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
            "), "
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
                "), "
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
                ")"
            ")"
        ")";
    // clang-format on

    // Act
    const std::string actual_info = compound_shape_n2_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithMultipleNesting, ShouldCorrectlyAddShape) {
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
            "), "
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
                "), "
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
                ")"
            "), "
            "Circle ("
                "Vector ((0.00, 0.00), (4.00, 0.00))"
            ")"
        ")";
    // clang-format

    // Act
    compound_shape_n2_.addShape(&circle_);
    const std::string actual_info = compound_shape_n2_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithMultipleNesting, ShouldCorrectlyDeleteShape) {
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
            "CompoundShape ("
                "Circle ("
                    "Vector ((0.00, 0.00), (4.00, 0.00))"
                "), "
                "Rectangle ("
                    "Vector ((0.00, 0.00), (3.00, 0.00)), "
                    "Vector ((0.00, 0.00), (0.00, 5.00))"
                "), "
                "CompoundShape ("
                    "Circle ("
                        "Vector ((0.00, 0.00), (4.00, 0.00))"
                    "), "
                    "Rectangle ("
                        "Vector ((0.00, 0.00), (3.00, 0.00)), "
                        "Vector ((0.00, 0.00), (0.00, 5.00))"
                    ")"
                ")"
            ")"
        ")";
    // clang-format on

    // Act
    compound_shape_n2_.deleteShape(&triangle_);
    const std::string actual_info = compound_shape_n2_.info();

    // Expect
    EXPECT_EQ(actual_info, expected_info);
}

TEST_F(CompoundShapeTestWithoutNesting, CreateBFSIteratorCorrectly) {
    // Arrange
    const auto it = compound_shape_.createBFSIterator();

    // Expect
    EXPECT_NE(it, nullptr);
    EXPECT_NO_THROW(it->first());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), true);
}

TEST_F(CompoundShapeTestWithoutNesting, CreateDFSIteratorCorrectly) {
    // Arrange
    const auto it = compound_shape_.createDFSIterator();

    // Expect
    EXPECT_NE(it, nullptr);
    EXPECT_NO_THROW(it->first());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), true);
}

TEST_F(CompoundShapeTestWithNesting, CreateBFSIteratorCorrectly) {
    // Arrange
    const auto it = compound_shape_n1_.createBFSIterator();

    // Expect
    EXPECT_NE(it, nullptr);
    EXPECT_NO_THROW(it->first());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &compound_shape_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), true);
}

TEST_F(CompoundShapeTestWithNesting, CreateDFSIteratorCorrectly) {
    // Arrange
    const auto it = compound_shape_n1_.createDFSIterator();

    // Expect
    EXPECT_NE(it, nullptr);
    EXPECT_NO_THROW(it->first());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &compound_shape_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), true);
}

TEST_F(CompoundShapeTestWithMultipleNesting, CreateBFSIteratorCorrectly) {
    // Arrange
    const auto it = compound_shape_n2_.createBFSIterator();

    // Expect
    EXPECT_NE(it, nullptr);
    EXPECT_NO_THROW(it->first());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &compound_shape_n1_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &compound_shape_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), true);
}

TEST_F(CompoundShapeTestWithMultipleNesting, CreateDFSIteratorCorrectly) {
    // Arrange
    const auto it = compound_shape_n2_.createDFSIterator();

    // Expect
    EXPECT_NE(it, nullptr);
    EXPECT_NO_THROW(it->first());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &compound_shape_n1_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &compound_shape_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &circle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &rectangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), false);
    EXPECT_EQ(it->currentItem(), &triangle_);
    EXPECT_NO_THROW(it->next());
    EXPECT_EQ(it->isDone(), true);
}

TEST_F(CompoundShapeTestWithNesting, ShouldCorrectlyGetPoints) {
    // Arrange
    const auto expectedPoint1 = Point{4.00, 4.00};
    const auto expectedPoint2 = Point{-4.00, -4.00};
    const auto expectedPoint3 = Point{0.00, 0.00};
    const auto expectedPoint4 = Point{4.00, 0.00};
    const auto expectedPoint5 = Point{0.00, 3.00};
    const auto expectedPoint6 = Point{3.00, 0.00};
    const auto expectedPoint7 = Point{0.00, 5.00};
    const auto expectedPoint8 = Point{3.00, 5.00};

    // Act
    const auto actualPoints = compound_shape_n1_.getPoints();

    std::vector<std::string> actualPointsInfo;
    for (auto &&point : actualPoints) {
        actualPointsInfo.push_back(point.info());
    }

    // Expect
    // Just like you said, we should find a way to remove the same-value points.
    EXPECT_EQ(actualPoints.size(), 8);
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint1.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint2.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint3.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint4.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint5.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint6.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint7.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint8.info()) != actualPointsInfo.cend());
}

TEST_F(CompoundShapeTestWithoutNesting, ShouldCorrectlyReplaceShape) {
    // Arrange
    const auto point1 = Point{4.00, 0.00};
    const auto point2 = Point{0.00, 3.00};

    const auto tmpV = TwoDimensionalVector{&point1, &point2};

    auto tmpCircle = Circle{tmpV};

    const std::string expected_info =
        // clang-format off
        "CompoundShape ("
            "Circle ("
                "Vector ((0.00, 0.00), (4.00, 0.00))"
            "), "
            "Circle ("
                "Vector ((4.00, 0.00), (0.00, 3.00))"
            "), "
            "Triangle ("
                "Vector ((0.00, 0.00), (4.00, 0.00)), "
                "Vector ((0.00, 0.00), (0.00, 3.00))"
            ")"
        ")";

    // Act
    compound_shape_.replace(&rectangle_, &tmpCircle);

    // Expect
    EXPECT_EQ(compound_shape_.info(), expected_info);
}
