#include "../../src/graphics/drawing.h"
#include "./observer/mock_observer.h"

class DrawingTest : public ::testing::Test {
   protected:
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

    const double DEVIATION = 0.0001;
    Circle *circle_ = new Circle{circle_vector_};
    Rectangle *rectangle_ = new Rectangle{rectangle_left_vector_, rectangle_right_vector_};
    Triangle *triangle_ = new Triangle{triangle_left_vector_, triangle_right_vector_};
    std::vector<Shape *> shapes_{circle_, rectangle_, triangle_};
    Drawing drawing{shapes_};
};

TEST_F(DrawingTest, attachShouldWorkCorrectly) {
    const auto observer = new MockObserver{};
    drawing.attach(observer);

    const auto justAddedObservers = drawing.getObservers();
    ASSERT_FALSE(justAddedObservers.empty());

    const auto lastAddedObserver = static_cast<MockObserver *>(justAddedObservers.at(0));
    EXPECT_TRUE(lastAddedObserver != nullptr);
    EXPECT_TRUE(observer == lastAddedObserver);

    delete observer;
}

TEST_F(DrawingTest, detachShouldWorkCorrectly) {
    const auto observer = new MockObserver{};
    drawing.attach(observer);
    drawing.detach(observer);

    const auto justAddedObservers = drawing.getObservers();
    EXPECT_TRUE(justAddedObservers.empty());

    delete observer;
}

TEST_F(DrawingTest, detachShouldThrowWhenNotFound) {
    const auto observer = new MockObserver{};
    EXPECT_THROW(drawing.detach(observer), Subject::ObserverNotFoundException);

    delete observer;
}

TEST_F(DrawingTest, notifyShouldWorkCorrectly) {
    const auto observer = new MockObserver{};
    drawing.attach(observer);
    drawing.notify();

    EXPECT_TRUE(observer->isUpdated());

    delete observer;
}

TEST_F(DrawingTest, shapesShouldBeCorrect) {
    const auto shapes = drawing.shapes();
    for (int i = 0; i < shapes_.size(); ++i) {
        EXPECT_EQ(shapes.at(i), shapes_.at(i));
    }
}
