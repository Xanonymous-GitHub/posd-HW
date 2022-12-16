#pragma once

#include "piece.h"
#include <vector>

class LinePiece : public Piece {
private:
    std::vector<SDL_Point> _points;
    const int _size;

public:
    LinePiece(
        SDL_Renderer *const renderer,
        SDL_Point *const points,
        const int &size) : Piece{renderer},
                           _size{size} {
        _points.assign(points, points + sizeof(points));
    }

    LinePiece(
        SDL_Renderer *const renderer,
        const std::vector<SDL_Point> &points,
        const int &size) : Piece{renderer},
                           _points{points},
                           _size{size} {}

    void draw() override {
        if (_size > 4) {
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0xBE, 0x0B, 0xFF);
        } else {
            SDL_SetRenderDrawColor(_renderer, 0xFF, 0x00, 0x6E, 0xFF);
        }

        SDL_RenderDrawLines(_renderer, _points.cbegin().base(), _size);
    }
};