#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/graphics/sdl_adapter.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "mock_sdl_renderer.h"

class SDLAdapterTest : public ::testing::Test {
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
    MockSDLRenderer mockSDLRenderer{};
    Circle circle_{circle_vector_};
    Rectangle rectangle_{rectangle_left_vector_, rectangle_right_vector_};
    Triangle triangle_{triangle_left_vector_, triangle_right_vector_};
};

TEST_F(SDLAdapterTest, initShouldBeCalledWhenAdapterIsInitialized) {
    const SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};
    EXPECT_TRUE(mockSDLRenderer.isInitCalled());
}

TEST_F(SDLAdapterTest, initCalledArgsShouldBeCorrect) {
    const SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};
    EXPECT_EQ(mockSDLRenderer.initWidth(), initWidth);
    EXPECT_EQ(mockSDLRenderer.initHeight(), initHeight);
}

TEST_F(SDLAdapterTest, widthAndHeightShouldBeGreaterThanZero) {
    const SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};
    EXPECT_ANY_THROW(SDLAdapter(0, 0, &mockSDLRenderer));
    EXPECT_ANY_THROW(SDLAdapter(-999, 87, &mockSDLRenderer));
    EXPECT_ANY_THROW(SDLAdapter(87, -999, &mockSDLRenderer));
    EXPECT_ANY_THROW(SDLAdapter(0, -0, &mockSDLRenderer));
}

TEST_F(SDLAdapterTest, renderDrawCircleCalledArgsShouldBeCorrect) {
    const SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};

    canvas.drawCircle(&circle_);

    const auto calledArgs = mockSDLRenderer.renderDrawCircleCalledArgs();
    const auto centerX = circle_.center().x();
    const auto centerY = circle_.center().y();
    const auto radius = circle_.radius();

    EXPECT_NEAR(calledArgs[0], centerX, DEVIATION);
    EXPECT_NEAR(calledArgs[1], centerY, DEVIATION);
    EXPECT_NEAR(calledArgs[2], radius, DEVIATION);
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRect) {
    const SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};
    canvas.drawRectangle(&rectangle_);

    EXPECT_EQ(mockSDLRenderer.renderDrawLinesCalledSize(), 8);

    const auto calledArgs = mockSDLRenderer.renderDrawLinesCalledPoints();

    EXPECT_NEAR(calledArgs[0], rectangle_vector_start_.x(), DEVIATION);
    EXPECT_NEAR(calledArgs[1], rectangle_vector_start_.y(), DEVIATION);
    EXPECT_NEAR(calledArgs[2], rectangle_right_vector_end_.x(), DEVIATION);
    EXPECT_NEAR(calledArgs[3], rectangle_right_vector_end_.y(), DEVIATION);
    EXPECT_NEAR(calledArgs[4], rectangle_left_vector_end_.x(), DEVIATION);
    EXPECT_NEAR(calledArgs[5], rectangle_left_vector_end_.y(), DEVIATION);
    EXPECT_NEAR(calledArgs[6], 3.0, DEVIATION);
    EXPECT_NEAR(calledArgs[7], 5.0, DEVIATION);
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRect2) {
    const Point a{4, 5}, b{8, 5}, c{8, 9};
    const TwoDimensionalVector aa{b, a}, bb{b, c};
    const Rectangle rec{aa, bb};

    const auto canvas = SDLAdapter{600, 600, &mockSDLRenderer};
    canvas.drawRectangle(&rec);

    EXPECT_EQ(mockSDLRenderer.renderDrawLinesCalledSize(), 8);

    const auto calledArgs = mockSDLRenderer.renderDrawLinesCalledPoints();

    EXPECT_NEAR(calledArgs[0], 4, DEVIATION);
    EXPECT_NEAR(calledArgs[1], 5, DEVIATION);
    EXPECT_NEAR(calledArgs[2], 4, DEVIATION);
    EXPECT_NEAR(calledArgs[3], 9, DEVIATION);
    EXPECT_NEAR(calledArgs[4], 8, DEVIATION);
    EXPECT_NEAR(calledArgs[5], 5, DEVIATION);
    EXPECT_NEAR(calledArgs[6], 8, DEVIATION);
    EXPECT_NEAR(calledArgs[7], 9, DEVIATION);
}

TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle) {
    const Point a{-2, -10}, b{-1, -13}, c{1, -10};
    const TwoDimensionalVector aa{a, b}, bb{a, c};
    const Triangle tri{aa, bb};

    const auto canvas = SDLAdapter{444, 444, &mockSDLRenderer};
    canvas.drawTriangle(&tri);

    EXPECT_EQ(mockSDLRenderer.renderDrawLinesCalledSize(), 6);

    const auto calledArgs = mockSDLRenderer.renderDrawLinesCalledPoints();

    EXPECT_NEAR(calledArgs[0], -1, DEVIATION);
    EXPECT_NEAR(calledArgs[1], -13, DEVIATION);
    EXPECT_NEAR(calledArgs[2], -2, DEVIATION);
    EXPECT_NEAR(calledArgs[3], -10, DEVIATION);
    EXPECT_NEAR(calledArgs[4], 1, DEVIATION);
    EXPECT_NEAR(calledArgs[5], -10, DEVIATION);
}

TEST_F(SDLAdapterTest, renderPresentShouldBeCalledWhenAdapterIsDisplayed) {
    const SDLAdapter canvas{initWidth, initHeight, &mockSDLRenderer};
    canvas.display();
    EXPECT_TRUE(mockSDLRenderer.isRenderPresentCalled());
}
