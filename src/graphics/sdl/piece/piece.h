#pragma once

#include <SDL2/SDL.h>

class Piece {
protected:
    SDL_Renderer *_renderer;

public:
    Piece(SDL_Renderer *const renderer) : _renderer{renderer} {}

    virtual void draw() = 0;
};