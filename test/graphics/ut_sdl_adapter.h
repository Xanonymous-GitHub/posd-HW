#include "../../src/circle.h"
#include "../../src/compound_shape.h"
#include "../../src/graphics/sdl_adapter.h"
#include "../../src/rectangle.h"
#include "../../src/shape.h"
#include "../../src/triangle.h"
#include "mock_sdl_renderer.h"

class SDLAdapterTest : public ::testing::Test {
protected:
    MockSDLRenderer mockSDLRenderer{};
    const SDLAdapter canvas{1024, 768, &mockSDLRenderer};
};

TEST_F(SDLAdapterTest, initShouldBeCalledWhenAdapterIsInitialized) {
    canvas.display();
}

// TEST_F(SDLAdapterTest, initCalledArgsShouldBeCorrect) {
//     canvas.display();
// }

// TEST_F(SDLAdapterTest, widthAndHeightShouldBeGreaterThanZero) {
//     canvas.display();
// }

// TEST_F(SDLAdapterTest, renderDrawCircleCalledArgsShouldBeCorrect) {
//     canvas.display();
// }

// TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForNonRotatedRect) {

//     // ...
//     Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
//     // ...
//     const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
//     // ...
//     delete[] calledPoints;
//     delete canvas;
// }

// TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect1) {
//     // ...
//     Canvas *canvas = new SDLAdapter(600, 600, mockSDLRenderer);
//     // ...
//     const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
//     // ...
//     delete[] calledPoints;
//     delete canvas;
// }

// TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect2) {
//     // ...
//     Canvas *canvas = new SDLAdapter(1, 1, mockSDLRenderer);
//     // ...
//     const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
//     // ...
//     delete[] calledPoints;
//     delete canvas;
// }

// TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForRotatedRect3) {
//     // ...
//     Canvas *canvas = new SDLAdapter(123, 654, mockSDLRenderer);
//     // ...
//     const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
//     // ...
//     delete[] calledPoints;
//     delete canvas;
// }

// TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle1) {
//     // ...
//     Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
//     // ...
//     const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
//     // ...
//     delete[] calledPoints;
//     delete canvas;
// }

// TEST_F(SDLAdapterTest, renderDrawLinesCalledArgsShouldBeCorrectForTriangle2) {
//     // ...
//     Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
//     // ...
//     const double *calledPoints = mockSDLRenderer->renderDrawLinesCalledPoints();
//     // ...
//     delete[] calledPoints;
//     delete canvas;
// }

// TEST_F(SDLAdapterTest, renderPresentShouldBeCalledWhenAdapterIsDisplayed) {
//     Canvas *canvas = new SDLAdapter(1024, 768, mockSDLRenderer);
//     // ...
//     delete canvas;
// }
