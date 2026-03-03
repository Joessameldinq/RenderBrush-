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
    bool erasing = false;

    int selectedColorIndex = 0;
    int brushSize          = 5;

    // helpers
    void drawSwatch(int index, SDL_Color color);
    void drawBrushControls();
    void drawClearButton();
    Point getSwatchPos(int index); // done
    Point getMinusButtonPos();
    Point getPlusButtonPos();
    Point getDisplayBoxPos();
    Point getEraserButtonPos();
    void  drawEraserButton();

public:
    Toolbar(SDL_Renderer* renderer,Canvas* canvas,Point leftUpCorner, int width, int height);
    void render();
    void handleClick(Point clicked);

    /**
     * Getters
     */
    int getHeight(){return height;}
};