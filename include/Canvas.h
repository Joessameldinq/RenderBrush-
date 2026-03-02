#pragma once
#include <SDL2/SDL.h>
#include "Utils.h"


class Canvas{
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int width,height;


    SDL_Color brushColor = {0,0,0,255};
    int brushSize = 5;
    bool drawing = false;
    int lastX = 0 , lastY = 0;
public:
    Canvas(SDL_Renderer* renderer,int width,int height);
    ~Canvas();

    void onMouseDown(int x,int y);
    void onMouseMove(int x,int y);
    void onMouseUp();

    void render();
    void clear();

    /**
     * Draweres
     */
    void clearScreen(); //Clear screen with white
    void drawPixel(Point point,SDL_Color color);
    void drawLine(Point start,Point end,SDL_Color color);
    void drawCircle(Point center,int radius,SDL_Color color);
    /**
     * Setters
     */
    void setColor(SDL_Color color);
    void setBrushSize(int size);
};