#include "../src/circle.h"
#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class ShapeTest : public ::testing::Test {
private:
    const Point _a{0, 0};
    const Point _b{4, 0};
    const Point _c{0, 3};
    const TwoDimensionalVector vec1_{_a, _b};
    const TwoDimensionalVector vec2_{_a, _c};
    Circle circle$_{vec1_};
    Triangle triangle$_{vec1_, vec2_};
    Rectangle rectangle$_{vec1_, vec2_};

    Shape *shapes$_[3] = {&circle$_, &triangle$_, &rectangle$_};
    CompoundShape compound$_{shapes$_, 3};

protected:
    const Shape &circle_{circle$_};
    const Shape &triangle_{triangle$_};
    const Shape &rectangle_{rectangle$_};
    const Shape &compound_{compound$_};
    const double DEVIATION = 0.0001;
};

TEST_F(ShapeTest, AreaWithPolymorphismShouldBeCorrect) {
    // Expect
    EXPECT_NEAR(circle_.area(), 50.26548245743669, DEVIATION);
    EXPECT_NEAR(triangle_.area(), 6, DEVIATION);
    EXPECT_NEAR(rectangle_.area(), 12, DEVIATION);
    EXPECT_NEAR(compound_.area(), 68.26548245743669, DEVIATION);
}

TEST_F(ShapeTest, PerimeterWithPolymorphismShouldBeCorrect) {
    // Expect
    EXPECT_NEAR(circle_.perimeter(), 25.132741228718345, DEVIATION);
    EXPECT_NEAR(triangle_.perimeter(), 12, DEVIATION);
    EXPECT_NEAR(rectangle_.perimeter(), 14, DEVIATION);
    EXPECT_NEAR(compound_.perimeter(), 51.132741228718345, DEVIATION);
}

TEST_F(ShapeTest, InfoWithPolymorphismShouldBeCorrect) {
    // Expect
    EXPECT_EQ(circle_.info(), "Circle (Vector ((0.00, 0.00), (4.00, 0.00)))");
    EXPECT_EQ(triangle_.info(), "Triangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
    EXPECT_EQ(rectangle_.info(), "Rectangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
    EXPECT_EQ(compound_.info(), "CompoundShape (Circle (Vector ((0.00, 0.00), (4.00, 0.00))), Triangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00))), Rectangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00))))");
}

TEST_F(ShapeTest, CreateBFSIteratorWithPolymorphismShouldBeCorrect) {
    // Act
    const auto circleBFSIterator = circle_.createIterator(IteratorFactory::getInstance("BFS"));
    const auto triangleBFSIterator = triangle_.createIterator(IteratorFactory::getInstance("BFS"));
    const auto rectangleBFSIterator = rectangle_.createIterator(IteratorFactory::getInstance("BFS"));
    const auto compoundBFSIterator = compound_.createIterator(IteratorFactory::getInstance("BFS"));

    // Expect
    EXPECT_THROW(circleBFSIterator->first(), Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(circleBFSIterator->isDone());

    EXPECT_THROW(triangleBFSIterator->first(), Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(triangleBFSIterator->isDone());

    EXPECT_THROW(rectangleBFSIterator->first(), Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(rectangleBFSIterator->isDone());

    EXPECT_NO_THROW(compoundBFSIterator->first());
    EXPECT_FALSE(compoundBFSIterator->isDone());

    delete circleBFSIterator;
    delete triangleBFSIterator;
    delete rectangleBFSIterator;
    delete compoundBFSIterator;
}

TEST_F(ShapeTest, CreateDFSIteratorWithPolymorphismShouldBeCorrect) {
    // Act
    const auto circleDFSIterator = circle_.createIterator(IteratorFactory::getInstance("DFS"));
    const auto triangleDFSIterator = triangle_.createIterator(IteratorFactory::getInstance("DFS"));
    const auto rectangleDFSIterator = rectangle_.createIterator(IteratorFactory::getInstance("DFS"));
    const auto compoundDFSIterator = compound_.createIterator(IteratorFactory::getInstance("DFS"));

    // Expect
    EXPECT_THROW(circleDFSIterator->first(), Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(circleDFSIterator->isDone());

    EXPECT_THROW(triangleDFSIterator->first(), Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(triangleDFSIterator->isDone());

    EXPECT_THROW(rectangleDFSIterator->first(), Iterator::MethodShouldNotBeRunError);
    EXPECT_TRUE(rectangleDFSIterator->isDone());

    EXPECT_NO_THROW(compoundDFSIterator->first());
    EXPECT_FALSE(compoundDFSIterator->isDone());

    delete circleDFSIterator;
    delete triangleDFSIterator;
    delete rectangleDFSIterator;
    delete compoundDFSIterator;
}
