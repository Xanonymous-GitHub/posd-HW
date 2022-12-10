#include "../src/triangle.h"

class TriangleTest : public ::testing::Test {
private:
    const Point _a{0, 0};
    const Point _b{4, 0};
    const Point _c{0, 3};
    const TwoDimensionalVector vec1_{_a, _b};
    const TwoDimensionalVector vec2_{_a, _c};

protected:
    TriangleTest() : triangle_{vec1_, vec2_} {}
    const double DEVIATION = 0.0001;
    const Triangle triangle_;
};

TEST_F(TriangleTest, ShouldCorrectlyCalculateArea) {
    // Expect
    EXPECT_NEAR(triangle_.area(), 6, DEVIATION);
}

TEST_F(TriangleTest, ShouldCorrectlyCalculatePerimeter) {
    // Expect
    EXPECT_NEAR(triangle_.perimeter(), 12, DEVIATION);
}

TEST_F(TriangleTest, ShouldCorrectlyPrintInfo) {
    // Expect
    EXPECT_EQ(triangle_.info(), "Triangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
}

TEST_F(TriangleTest, IllegalTriangle) {
    // Arrange
    const Point o{0, 0}, o_1{3, 0}, o_2{-3, 0};
    const Point k{1, 1}, k_1{4, 1}, k_2{-4, 1};
    const Point l{0, 2}, l_1{5, 2}, l_2{-5, 2};

    const TwoDimensionalVector vec1{&o, &o_1}, vec2{&o, &o_2}, vec3{&k, &k_1}, vec4{&k, &k_2}, vec5{&k_1, &k_2}, vec6{&o, &l};

    // Expect
    EXPECT_ANY_THROW(Triangle(vec1, vec2));
    EXPECT_ANY_THROW(Triangle(vec3, vec1));
    EXPECT_ANY_THROW(Triangle(vec5, vec6));
}

TEST_F(TriangleTest, CreatedBFSIteratorShouldThrowWhenCallingFirst) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW({ it->first(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(TriangleTest, CreatedDFSIteratorShouldThrowWhenCallingFirst) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW({ it->first(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(TriangleTest, CreatedBFSIteratorShouldThrowWhenCallingCurrentItem) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW({ it->currentItem(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(TriangleTest, CreatedDFSIteratorShouldThrowWhenCallingCurrentItem) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW({ it->currentItem(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(TriangleTest, CreatedBFSIteratorShouldThrowWhenCallingNext) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW({ it->next(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(TriangleTest, CreatedDFSIteratorShouldThrowWhenCallingNext) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW({ it->next(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(TriangleTest, CreatedBFSIteratorShouldGetTRUEWhenCallingIsDone) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_TRUE(it->isDone());

    delete it;
}

TEST_F(TriangleTest, CreatedDFSIteratorShouldGetTRUEWhenCallingIsDone) {
    // Act
    const auto it = triangle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_TRUE(it->isDone());

    delete it;
}

TEST_F(TriangleTest, ShouldCorrectlyGetPoints) {
    // Arrange
    const auto expectedPoint1 = Point{0.00, 0.00};
    const auto expectedPoint2 = Point{4.00, 0.00};
    const auto expectedPoint3 = Point{0.00, 3.00};

    // Act
    const auto actualPoints = triangle_.getPoints();

    std::vector<std::string> actualPointsInfo;
    for (const auto &point : actualPoints) {
        actualPointsInfo.push_back(point.info());
    }

    // Expect
    EXPECT_EQ(actualPoints.size(), 3);
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint1.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint2.info()) != actualPointsInfo.cend());
    EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint3.info()) != actualPointsInfo.cend());
}
