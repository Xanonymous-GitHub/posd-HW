#include "../../src/compound_shape.h"
#include "../../src/iterator/dfs_compound_iterator.h"

class DfsCompoundIteratorTestBase : public ::testing::Test {
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

class Lv0DfsCompoundIteratorTest : public DfsCompoundIteratorTestBase {
protected:
    /**
     * lv0_compound_shape_
     */
    const CompoundShape lv0_compound_shape_{};
};

class Lv1DfsCompoundIteratorTest : public DfsCompoundIteratorTestBase {
protected:
    /**
     * lv1_compound_shape_
     * |
     * |--- circle_
     */
    const Shape *const content_of_lv1_width_1_compound_shape_[1] = {&circle_};
    const CompoundShape lv1_width_1_compound_shape_{content_of_lv1_width_1_compound_shape_, 1};

    /**
     * lv1_compound_shape_
     * |
     * |--- circle_
     * |--- rectangle_
     */
    const Shape *const content_of_lv1_width_2_compound_shape_[2] = {&circle_, &rectangle_};
    const CompoundShape lv1_width_2_compound_shape_{content_of_lv1_width_2_compound_shape_, 2};

    /**
     * lv1_compound_shape_
     * |
     * |--- circle_
     * |--- rectangle_
     * |--- triangle_
     */
    const Shape *const content_of_lv1_width_3_compound_shape_[3] = {&circle_, &rectangle_, &triangle_};
    const CompoundShape lv1_width_3_compound_shape_{content_of_lv1_width_3_compound_shape_, 3};
};

class Lv2DfsCompoundIteratorTest : public Lv1DfsCompoundIteratorTest {
protected:
    /**
     * lv2_compound_shape_
     * |
     * |--- lv1_width_1_compound_shape_
     * |    |
     * |    |--- circle_
     */
    const Shape *const content_of_lv2_width_1_compound_shape_[1] = {&lv1_width_1_compound_shape_};
    const CompoundShape lv2_width_1_compound_shape_{content_of_lv2_width_1_compound_shape_, 1};

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
    const Shape *const content_of_lv2_width_2_compound_shape_[2] = {&lv1_width_2_compound_shape_, &lv1_width_1_compound_shape_};
    const CompoundShape lv2_width_2_compound_shape_{lv1_width_2_compound_shape_, lv1_width_1_compound_shape_};

    /**
     * lv2_compound_shape_
     * |
     * |--- circle_
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
    const Shape *const content_of_lv2_width_4_compound_shape_[4] = {&circle_, &lv1_width_1_compound_shape_, &lv1_width_2_compound_shape_, &lv1_width_3_compound_shape_};
    const CompoundShape lv2_width_4_compound_shape_{content_of_lv2_width_4_compound_shape_, 4};
};

TEST_F(Lv0DfsCompoundIteratorTest, Lv0DfsCompoundIteratorShouldIterateOverZeroShapes) {
    // Arrange
    const auto it = lv0_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{};

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        FAIL();
    }
}

TEST_F(Lv1DfsCompoundIteratorTest, Lv1Width1DfsCompoundIteratorShouldIterateOverOneShape) {
    // Arrange
    const auto it = lv1_width_1_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{&circle_};
    int i = 0;

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        EXPECT_EQ(it->currentItem(), expectedTraversalHistory[i++]);
    }

    EXPECT_EQ(i, expectedTraversalHistory.size());
}

TEST_F(Lv1DfsCompoundIteratorTest, Lv1Width2DfsCompoundIteratorShouldIterateOverTwoShapes) {
    // Arrange
    const auto it = lv1_width_2_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{&circle_, &rectangle_};
    int i = 0;

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        EXPECT_EQ(it->currentItem(), expectedTraversalHistory[i++]);
    }

    EXPECT_EQ(i, expectedTraversalHistory.size());
}

TEST_F(Lv1DfsCompoundIteratorTest, Lv1Width3DfsCompoundIteratorShouldIterateOverThreeShapes) {
    // Arrange
    const auto it = lv1_width_3_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{&circle_, &rectangle_, &triangle_};
    int i = 0;

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        EXPECT_EQ(it->currentItem(), expectedTraversalHistory[i++]);
    }

    EXPECT_EQ(i, expectedTraversalHistory.size());
}

TEST_F(Lv2DfsCompoundIteratorTest, Lv2Width1DfsCompoundIteratorShouldIterateCorrectly) {
    // Arrange
    const auto it = lv2_width_1_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{&lv1_width_1_compound_shape_, &circle_};
    int i = 0;

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        EXPECT_EQ(it->currentItem(), expectedTraversalHistory[i++]);
    }

    EXPECT_EQ(i, expectedTraversalHistory.size());
}

TEST_F(Lv2DfsCompoundIteratorTest, Lv2Width2DfsCompoundIteratorShouldIterateCorrectly) {
    // Arrange
    const auto it = lv2_width_2_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{
        &lv1_width_2_compound_shape_,
        &circle_,
        &rectangle_,
        &lv1_width_1_compound_shape_,
        &circle_,
    };
    int i = 0;

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        EXPECT_EQ(it->currentItem(), expectedTraversalHistory[i++]);
    }

    EXPECT_EQ(i, expectedTraversalHistory.size());
}

TEST_F(Lv2DfsCompoundIteratorTest, Lv2Width4DfsCompoundIteratorShouldIterateCorrectly) {
    // Arrange
    const auto it = lv2_width_4_compound_shape_.createDFSIterator();

    // Act
    const auto expectedTraversalHistory = std::vector<const Shape *>{
        &circle_,
        &lv1_width_1_compound_shape_,
        &circle_,
        &lv1_width_2_compound_shape_,
        &circle_,
        &rectangle_,
        &lv1_width_3_compound_shape_,
        &circle_,
        &rectangle_,
        &triangle_,
    };
    int i = 0;

    // Expect
    for (it->first(); !it->isDone(); it->next()) {
        EXPECT_EQ(it->currentItem(), expectedTraversalHistory[i++]);
    }

    EXPECT_EQ(i, expectedTraversalHistory.size());
}
