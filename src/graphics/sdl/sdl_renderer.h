#pragma once

#include "./piece/cir_piece.h"
#include "./piece/line_piece.h"
#include "sdl.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class SDLRenderer : public SDL {
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    double _xOffset;
    double _yOffset;
    double _scale;

    SDL_Window *_window = nullptr;
    SDL_Renderer *_renderer = nullptr;
    std::vector<std::unique_ptr<Piece>> _pieces;

public:
    SDLRenderer(const double &scale = 1.0) : _scale(scale) {}

    ~SDLRenderer() {
        destroy();
    }

    void init(int width, int height) override {
        SCREEN_WIDTH = width;
        SCREEN_HEIGHT = height;
        _xOffset = SCREEN_WIDTH / 2;
        _yOffset = SCREEN_HEIGHT / 2;

        bool success = true;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
            }

            SDL_DisplayMode DM;
            int displayWidth = SCREEN_WIDTH / 2;
            int displayHeight = SCREEN_HEIGHT / 2;

            if (SDL_GetCurrentDisplayMode(0, &DM) == 0) {
                displayWidth = DM.w;
                displayHeight = DM.h;
            } else {
                std::cout << "Failed to get the display size. Use the default position (0, 0)." << std::endl;
            }

            _window = SDL_CreateWindow(
                "Your Shapes",
                (displayWidth / 2) - (SCREEN_WIDTH / 2),
                (displayHeight / 2) - (SCREEN_HEIGHT / 2),
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                SDL_WINDOW_SHOWN);

            if (_window == nullptr) {
                std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
                success = false;
            } else {
                _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

                if (_renderer == nullptr) {
                    std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
                    success = false;
                } else {
                    SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags)) {
                        std::cout << "SDL_image could not initialize! SDL_image Error: "
                                  << IMG_GetError() << std::endl;
                        success = false;
                    }
                }
            }
        }
        if (!success) {
            std::cout << "Failed to initialize!" << std::endl;
        }
    };

    void renderDrawLines(double *const points, int size) override {
        std::vector<SDL_Point> sdlPoints(size / 2 + 1);

        for (int i = 0; i < size; i += 2) {
            sdlPoints[i / 2] = SDL_Point{
                (int)(_xOffset + points[i] * _scale),
                (int)(_yOffset - points[i + 1] * _scale)};
        }

        sdlPoints[size / 2] = SDL_Point{
            (int)(_xOffset + points[0] * _scale),
            (int)(_yOffset - points[1] * _scale)};

        _pieces.push_back(std::make_unique<LinePiece>(_renderer, sdlPoints, size / 2 + 1));
    };

    void renderDrawCircle(double centreX, double centreY, double radius) override {
        _pieces.push_back(
            std::make_unique<CirPiece>(
                _renderer,
                (int)(_xOffset + centreX * _scale),
                (int)(_yOffset - centreY * _scale),
                (int)(radius * _scale)));
    };

    void renderPresent() override {
        SDL_Event e;
        bool quit = false;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            SDL_SetRenderDrawColor(_renderer, 0x00, 0x1D, 0x3D, 0xFF);
            SDL_RenderClear(_renderer);
            SDL_SetRenderDrawColor(_renderer, 0xED, 0xED, 0xE9, 0xFF);

            for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
                SDL_RenderDrawPoint(_renderer, SCREEN_WIDTH / 2, i);
            }

            for (int i = 0; i < SCREEN_WIDTH; i += 4) {
                SDL_RenderDrawPoint(_renderer, i, SCREEN_HEIGHT / 2);
            }

            for (auto &&it : _pieces) {
                it->draw();
            }

            SDL_RenderPresent(_renderer);
            SDL_Delay(100);
        }
    }

    void destroy() override {
        if (_renderer != nullptr) {
            SDL_DestroyRenderer(_renderer);
            _renderer = nullptr;
        }

        if (_window != nullptr) {
            SDL_DestroyWindow(_window);
            _window = nullptr;
        }

        IMG_Quit();
        SDL_Quit();
    }
};