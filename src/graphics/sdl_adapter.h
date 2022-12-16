#pragma once

#include "../circle.h"
#include "../rectangle.h"
#include "../triangle.h"
#include "./sdl/sdl.h"
#include "canvas.h"

#include <memory>
#include <vector>

class SDLAdapter : public Canvas {
private:
    SDL *sdl_;

    void delegateToPolygonXYPairsExtractionFrom_(const Shape &s) const {
        const auto points = s.getPoints();
        std::vector<double> xyPairs;

        for (auto &&it : points) {
            xyPairs.push_back(it.x());
            xyPairs.push_back(it.y());
        }

        sdl_->renderDrawLines(xyPairs.begin().base(), xyPairs.size());
    }

public:
    SDLAdapter(const int &width, const int &height, SDL *const sdl) : sdl_{sdl} {}

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

        delegateToPolygonXYPairsExtractionFrom_(*rect);
    }

    void display() const override {
        sdl_->renderPresent();
    }
};
