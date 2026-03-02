#pragma once
#include <SDL2/SDL.h>

namespace Colors {
    constexpr SDL_Color BLACK   = {0,   0,   0,   255};
    constexpr SDL_Color WHITE   = {255, 255, 255, 255};
    constexpr SDL_Color RED     = {255, 0,   0,   255};
    constexpr SDL_Color GREEN   = {0,   200, 0,   255};
    constexpr SDL_Color BLUE    = {0,   0,   255, 255};
    constexpr SDL_Color YELLOW  = {255, 255, 0,   255};
    constexpr SDL_Color ORANGE  = {255, 165, 0,   255};
    constexpr SDL_Color PURPLE  = {128, 0,   128, 255};
    constexpr SDL_Color PINK    = {255, 105, 180, 255};
    constexpr SDL_Color BROWN   = {139, 69,  19,  255};

    // useful to iterate over all colors in toolbar
    constexpr SDL_Color ALL[10] = {
        BLACK, WHITE, RED, GREEN, BLUE,
        YELLOW, ORANGE, PURPLE, PINK, BROWN
    };
}