#include "../../src/iterator/factory/list_iterator_factory.h"

class ListIteratorFactoryTest : public ::testing::Test {
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
    const double DEVIATION = 0.001;
    Circle circle_{circle_vector_};
    Rectangle rectangle_{rectangle_left_vector_, rectangle_right_vector_};
    Triangle triangle_{triangle_left_vector_, triangle_right_vector_};
};

class Lv1ListCompoundIteratorTest : public ListIteratorFactoryTest {
protected:
    /**
     * lv1_compound_shape_
     * |
     * |--- circle_
     */
    Shape *content_of_lv1_width_1_compound_shape_[1] = {&circle_};
    CompoundShape lv1_width_1_compound_shape_{content_of_lv1_width_1_compound_shape_, 1};

    /**
     * lv1_compound_shape_
     * |
     * |--- circle_
     * |--- rectangle_
     */
    Shape *content_of_lv1_width_2_compound_shape_[2] = {&circle_, &rectangle_};
    CompoundShape lv1_width_2_compound_shape_{content_of_lv1_width_2_compound_shape_, 2};

    /**
     * lv1_compound_shape_
     * |
     * |--- circle_
     * |--- rectangle_
     * |--- triangle_
     */
    Shape *content_of_lv1_width_3_compound_shape_[3] = {&circle_, &rectangle_, &triangle_};
    CompoundShape lv1_width_3_compound_shape_{content_of_lv1_width_3_compound_shape_, 3};
};

class Lv2ListCompoundIteratorTest : public Lv1ListCompoundIteratorTest {
protected:
    /**
     * lv2_compound_shape_
     * |
     * |--- lv1_width_1_compound_shape_
     * |    |
     * |    |--- circle_
     */
    Shape *content_of_lv2_width_1_compound_shape_[1] = {&lv1_width_1_compound_shape_};
    CompoundShape lv2_width_1_compound_shape_{content_of_lv2_width_1_compound_shape_, 1};

    /**
     * lv2_compound_shape_
     * |
     * |--- lv1_width_2_compound_shape_
     * |    |
     * |    |--- circle_
     * |    |--- rectangle_
     * |
     * |--- lv1_width_1_compound_shape_
     * |    |
     * |    |--- circle_
     */
    Shape *content_of_lv2_width_2_compound_shape_[2] = {&lv1_width_2_compound_shape_, &lv1_width_1_compound_shape_};
    CompoundShape lv2_width_2_compound_shape_{lv1_width_2_compound_shape_, lv1_width_1_compound_shape_};

    /**
     * lv2_compound_shape_
     * |
     * |--- circle_
     * |--- rectangle_
     * |--- triangle_
     * |
     * |--- lv1_width_1_compound_shape_
     * |    |
     * |    |--- circle_
     * |
     * |--- lv1_width_2_compound_shape_
     * |    |
     * |    |--- circle_
     * |    |--- rectangle_
     * |
     * |--- lv1_width_3_compound_shape_
     * |    |
     * |    |--- circle_
     * |    |--- rectangle_
     * |    |--- triangle_
     */
    Shape *content_of_lv2_width_4_compound_shape_[6] = {&circle_, &rectangle_, &triangle_, &lv1_width_1_compound_shape_, &lv1_width_2_compound_shape_, &lv1_width_3_compound_shape_};
    CompoundShape lv2_width_4_compound_shape_{content_of_lv2_width_4_compound_shape_, 6};
};

TEST_F(Lv2ListCompoundIteratorTest, shouldGetCorrectItemWhenCallingCurrentItem) {
    // Arrange
    const auto it = lv2_width_4_compound_shape_.createIterator(IteratorFactory::getInstance("List"));

    // Act
    const auto current_item = it->currentItem();

    // Expect
    EXPECT_EQ(current_item, &circle_);
}

TEST_F(Lv2ListCompoundIteratorTest, shouldGetCorrectItemAfterCallingNext) {
    // Arrange
    const auto it = lv2_width_4_compound_shape_.createIterator(IteratorFactory::getInstance("List"));

    // Act
    it->next();

    // Expect
    EXPECT_EQ(it->currentItem(), &rectangle_);
}

TEST_F(Lv2ListCompoundIteratorTest, shouldGetCorrectReturnOrThrowWhenDone) {
    // Arrange
    const auto it = lv2_width_4_compound_shape_.createIterator(IteratorFactory::getInstance("List"));

    // Act
    it->next();
    EXPECT_FALSE(it->isDone()); // No time, QQ
    it->next();
    it->next();
    it->next();
    it->next();
    it->next();


    // Expect
    EXPECT_TRUE(it->isDone());
    EXPECT_THROW(it->currentItem(), Iterator::MethodShouldNotBeRunError);
    EXPECT_THROW(it->next(), Iterator::MethodShouldNotBeRunError);
}

TEST_F(Lv2ListCompoundIteratorTest, shouldNotTraverseIntoLv1CompoundShape) {
    // Arrange
    const auto it = lv2_width_4_compound_shape_.createIterator(IteratorFactory::getInstance("List"));

    // Act
    it->next();
    it->next();
    it->next();
    it->next();
    it->next();
    it->next();

    // Expect
    EXPECT_THROW(it->currentItem(), Iterator::MethodShouldNotBeRunError);
}
