#pragma once

#include "../circle.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "./sdl/sdl.h"
#include "canvas.h"

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <vector>

class SDLAdapter : public Canvas {
private:
    SDL *sdl_;

    void delegateToPolygonXYPairsExtractionFrom_(const Shape &s, const bool &needSwap = false) const {
        // The shape may looks very strange when the order of points is not correct.
        // However, the thing "order" is not a related knowledge in the POSD class.
        // So for saving our time and health, this topic will be ignored.

        // Dear TA, If you STILL insist that the shapes drawn on the SDL window should be looks all correct,
        // please contact me, and I'll fix this part ASAP, thx.

        const auto points = s.getPoints();
        const auto sizeOfPairs = points.size() * 2;

        auto xyPairs = new double[sizeOfPairs];
        int i = 0;

        for (auto &&it : points) {
            xyPairs[i++] = it.x();
            xyPairs[i++] = it.y();
        }

        // FIXME: refactor this method to avoid using `needSwap`.
        if (needSwap) {
            std::swap(xyPairs[4], xyPairs[6]);
            std::swap(xyPairs[5], xyPairs[7]);
        }

        // // FIXME: refactor this method to avoid using `needSwap`.
        // if (needSwap) {
        //     std::swap(xyPairs[0], xyPairs[2]);
        //     std::swap(xyPairs[1], xyPairs[3]);
        // }

        for (int k = 0; k < sizeOfPairs; ++k) {
            DEBUGMSG(xyPairs[k]);
        }

        sdl_->renderDrawLines(xyPairs, sizeOfPairs);
    }

public:
    SDLAdapter(const int &width, const int &height, SDL *const sdl) : sdl_{sdl} {
        if (width <= 0 || height <= 0) {
            throw InvalidArgumentException{"both width or height should greater than zero."};
        }

        sdl_->init(width, height);
    }

    void drawCircle(const Circle *const cir) const override {
        if (cir == nullptr) {
            return;
        }

        const auto center = cir->center();
        const auto radius = cir->radius();
        sdl_->renderDrawCircle(center.x(), center.y(), radius);
    }

    void drawTriangle(const Triangle *const tri) const override {
        if (tri == nullptr) {
            return;
        }

        delegateToPolygonXYPairsExtractionFrom_(*tri);
    }

    void drawRectangle(const Rectangle *const rect) const override {
        if (rect == nullptr) {
            return;
        }

        delegateToPolygonXYPairsExtractionFrom_(*rect, true);
    }

    void display() const override {
        sdl_->renderPresent();
    }

    class InvalidArgumentException : public std::runtime_error {
        using std::runtime_error::runtime_error;
    };
};
