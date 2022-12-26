#include "../../src/graphics/real_canvas.h"
#include "../../src/graphics/sdl_adapter.h"
#include "mock_sdl_renderer.h"

class RealCanvasTest : public ::testing::Test {
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
    const int initWidth = 1024;
    const int initHeight = 768;
    Circle *circle_ = new Circle{circle_vector_};
    Rectangle *rectangle_ = new Rectangle{rectangle_left_vector_, rectangle_right_vector_};
    Triangle *triangle_ = new Triangle{triangle_left_vector_, triangle_right_vector_};
    std::vector<Shape *> shapes_{circle_, triangle_, rectangle_};

    MockSDLRenderer mockSDLRenderer{};
    SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};
    Drawing drawing{shapes_};
    RealCanvas realCanvas{&canvas, &drawing};
};

TEST_F(RealCanvasTest, updateShouldBeCalledSuccessfully1) {
    realCanvas.update();

    /**
     * Since the `shapes_` here is consisted of circle->triangle->rectangle,
     * The history inside `mockSDLRenderer` will only stored the last circle's and last rectangle's.
     */

    const auto circleCalledArgs = mockSDLRenderer.renderDrawCircleCalledArgs();

    const auto centerX = circle_->center().x();
    const auto centerY = circle_->center().y();
    const auto radius = circle_->radius();

    EXPECT_NEAR(circleCalledArgs[0], centerX, DEVIATION);
    EXPECT_NEAR(circleCalledArgs[1], centerY, DEVIATION);
    EXPECT_NEAR(circleCalledArgs[2], radius, DEVIATION);
}

TEST_F(RealCanvasTest, updateShouldBeCalledSuccessfully2) {
    realCanvas.update();

    /**
     * Since the `shapes_` here is consisted of circle->triangle->rectangle,
     * The history inside `mockSDLRenderer` will only stored the last circle's and last rectangle's.
     */

    const auto lineCalledArgs = mockSDLRenderer.renderDrawLinesCalledPoints();

    EXPECT_NEAR(lineCalledArgs[0], 0, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[1], 0, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[2], 0, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[3], 5, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[4], 3, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[5], 5, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[6], 3, DEVIATION);
    EXPECT_NEAR(lineCalledArgs[7], 0, DEVIATION);

    delete[] lineCalledArgs;
}
