#pragma once

#include "./sdl/sdl.h"
#include "canvas.h"
#include <memory>

class SDLAdapter : public Canvas {
private:
    std::shared_ptr<SDL> sdl_;

public:
    SDLAdapter(const int &width, const int &height, SDL *const sdl) : sdl_{std::shared_ptr<SDL>(sdl)} {}

    SDLAdapter(const int &width, const int &height, const std::shared_ptr<SDL> &sdl) : sdl_{sdl} {}

    void drawCircle(const Circle *const cir) const override {
    }

    void drawTriangle(const Triangle *const tri) const override {
    }

    void drawRectangle(const Rectangle *const rect) const override {
    }

    void display() const override {
    }
};
