#pragma once
#include <SDL2/SDL.h>
#include "Utils.h"
#include "Colors.h"
#include "Canvas.h"

class Toolbar {
private:
    SDL_Renderer* renderer;
    Canvas* canvas = nullptr; //To set the color of the brush
    Point leftUpCorner;         // top-left corner of toolbar
    int width, height; // toolbar dimensions
    int swatchSize;
    int padding    = 5;

    int selectedColorIndex = 0;
    int brushSize          = 5;

    // helpers
    void drawSwatch(int index, SDL_Color color);
    void drawBrushControls();
    void drawClearButton();

public:
    Toolbar(SDL_Renderer* renderer,Canvas* canvas,Point leftUpCorner, int width, int height);
    void render();
    void handleClick(int x, int y);
};