#include "../src/circle.h"
#include "../src/point.h"
#include "../src/rectangle.h"
#include "../src/shape.h"
#include "../src/triangle.h"
#include "../src/two_dimensional_vector.h"

class ShapeTest : public ::testing::Test {
protected:
    ShapeTest() : vec1{TwoDimensionalVector(&_a, &_b)}, vec2{TwoDimensionalVector(&_a, &_c)} {}
    const double DEVIATION = 0.0001;
    const TwoDimensionalVector vec1;
    const TwoDimensionalVector vec2;
    const Point _a{0, 0};
    const Point _b{4, 0};
    const Point _c{0, 3};
};

TEST_F(ShapeTest, AreaWithPolymorphismShouldBeCorrect) {
    // Arrange
    const Shape *circle = new Circle{&vec1};
    const Shape *triangle = new Triangle{&vec1, &vec2};

    // Expect
    EXPECT_NEAR(circle->area(), 50.26548245743669, DEVIATION);
    EXPECT_NEAR(triangle->area(), 6, DEVIATION);
}

TEST_F(ShapeTest, PerimeterWithPolymorphismShouldBeCorrect) {
    // Arrange
    const Shape *circle = new Circle{&vec1};
    const Shape *triangle = new Triangle{&vec1, &vec2};

    // Expect
    EXPECT_NEAR(circle->perimeter(), 25.132741228718345, DEVIATION);
    EXPECT_NEAR(triangle->perimeter(), 12, DEVIATION);
}

TEST_F(ShapeTest, InfoWithPolymorphismShouldBeCorrect) {
    // Arrange
    const Shape *circle = new Circle{&vec1};
    const Shape *triangle = new Triangle{&vec1, &vec2};

    // Expect
    EXPECT_EQ(circle->info(), "Circle (Vector ((0.00, 0.00), (4.00, 0.00)))");
    EXPECT_EQ(triangle->info(), "Triangle (Vector ((0.00, 0.00), (4.00, 0.00)), Vector ((0.00, 0.00), (0.00, 3.00)))");
}
