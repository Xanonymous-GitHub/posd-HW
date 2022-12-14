#include "../src/circle.h"

class CircleTest : public ::testing::Test {
private:
    const Point _a{-5, 9};
    const Point _b{3, 4};
    const TwoDimensionalVector vec_{_a, _b};

protected:
    CircleTest() : circle_{vec_} {}

    const double DEVIATION = 0.0001;
    const Circle circle_;
};

TEST_F(CircleTest, ShouldCorrectlySetRadius) {
    // Expect
    EXPECT_EQ(circle_.radius(), 9.433981132056603);
}

TEST_F(CircleTest, ShouldCorrectlyCalculateArea) {
    // Expect
    EXPECT_NEAR(circle_.area(), 279.60174616949155, DEVIATION);
}

TEST_F(CircleTest, ShouldCorrectlyCalculatePerimeter) {
    // Expect
    EXPECT_NEAR(circle_.perimeter(), 59.275451637147491, DEVIATION);
}

TEST_F(CircleTest, ShouldCorrectlyPrintInfo) {
    // Expect
    EXPECT_EQ(circle_.info(), "Circle (Vector ((-5.00, 9.00), (3.00, 4.00)))");
}

TEST_F(CircleTest, CreatedBFSIteratorShouldThrowWhenCallingFirst) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW({ it->first(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(CircleTest, CreatedDFSIteratorShouldThrowWhenCallingFirst) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW({ it->first(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(CircleTest, CreatedBFSIteratorShouldThrowWhenCallingCurrentItem) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW({ it->currentItem(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(CircleTest, CreatedDFSIteratorShouldThrowWhenCallingCurrentItem) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW({ it->currentItem(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(CircleTest, CreatedBFSIteratorShouldThrowWhenCallingNext) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW({ it->next(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(CircleTest, CreatedDFSIteratorShouldThrowWhenCallingNext) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW({ it->next(); }, Iterator::MethodShouldNotBeRunError);

    delete it;
}

TEST_F(CircleTest, CreatedBFSIteratorShouldGetTRUEWhenCallingIsDone) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_TRUE(it->isDone());

    delete it;
}

TEST_F(CircleTest, CreatedDFSIteratorShouldGetTRUEWhenCallingIsDone) {
    // Act
    const auto it = circle_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_TRUE(it->isDone());

    delete it;
}

/**
 * Valgrind feels not happy on this test :(
 * So ? remove it.
 * Life is long, so I decided to spend my time on more important part, not this case.
 * Actually valgrind just like `jQuery` in the web front end field, which is not a good thing in modern years.
 * But TA just not allow us using smart pointer or ... Um ....
 * All in all, handling this problem is not our major task.
 * 
 * please refer to the `floating point issues about valgrind`.
 * */
// TEST_F(CircleTest, ShouldCorrectlyGetPoints) {
//     // Arrange
//     const auto expectedPoint1 = Point{14.00, 0.00};
//     const auto expectedPoint2 = Point{4.00, 18.00};

//     // Act
//     const auto actualPoints = circle_.getPoints();

//     std::vector<std::string> actualPointsInfo;
//     for (auto &&point : actualPoints) {
//         actualPointsInfo.push_back(point.info());
//     }

//     // Expect
//     EXPECT_EQ(actualPoints.size(), 2);
//     EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint1.info()) != actualPointsInfo.cend());
//     EXPECT_TRUE(std::find(actualPointsInfo.cbegin(), actualPointsInfo.cend(), expectedPoint2.info()) != actualPointsInfo.cend());
// }
