#include "../include/Canvas.h"
#include <cmath>
#include <string>

Canvas::Canvas(SDL_Renderer* renderer,int width ,int height)
    :renderer(renderer) , width(width),height(height)
{
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width,height
    );

    clear(); // start with white bg
}

Canvas::~Canvas(){
    if(texture)
        SDL_DestroyTexture(texture);
}

void Canvas::drawCircle(Point center,int radius,SDL_Color color){
    SDL_SetRenderTarget(renderer,texture);
    SDL_SetRenderDrawColor(renderer,color.r,color.g,color.b,color.a);

    for(int dy = -radius ; dy <= radius ;dy++){
        for(int dx = -radius;dx <= radius;dx++){
            if(dx*dx + dy*dy <= radius*radius)
                SDL_RenderDrawPoint(renderer,center.x + dx, center.y + dy);
        }
    }
    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::drawLine(Point start,Point end,SDL_Color color){
    int dx = end.x - start.x, dy = end.y - start.y;
    int steps = std::max(std::abs(dx),std::abs(dy));

    if(steps == 0){
        drawCircle(start,brushSize,color);
        return;
    }
    float xStep = (float)dx / steps;
    float yStep = (float)dy / steps;
    for (int i = 0; i <= steps; i++) {
        Point p = { start.x + (int)(xStep * i), start.y + (int)(yStep * i) };
        drawCircle(p,brushSize,color);
    }
}

void Canvas::drawPixel(Point point,SDL_Color color){
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(renderer, point.x, point.y);
    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::clearScreen(){
    SDL_SetRenderTarget(renderer, texture);
    SDL_Color white = {255,255,255,255};
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}
void Canvas::clear(){
    clearScreen();
}

void Canvas::onMouseDown(int x,int y){
    drawing = true;
    lastX = x ; lastY = y;
    drawCircle({x,y},brushSize,brushColor);
}

void Canvas::onMouseMove(int x,int y){
    if(!drawing)return;
    drawLine({lastX,lastY},{x,y},brushColor);
    lastX = x, lastY = y;
}
void Canvas::onMouseUp(){
    drawing = false;
}
void Canvas::setColor(SDL_Color color) { brushColor = color; }
void Canvas::setBrushSize(int size)    { brushSize  = size;  }

void Canvas::render() {
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
}

void Canvas::save(const std::string& path){
    SDL_Surface* surface = SDL_CreateRGBSurface(
        0, width, height, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF
    );
    if (!surface) {
        SDL_Log("SDL_CreateRGBSurface Error: %s", SDL_GetError());
        return;
    }

    // Read pixels from texture into surface
    SDL_SetRenderTarget(renderer,texture);
    SDL_RenderReadPixels(
        renderer,nullptr,
        SDL_PIXELFORMAT_RGBA8888,
        surface->pixels,surface->pitch
    );
    SDL_SetRenderTarget(renderer, nullptr);

    // Save as png
    if(IMG_SavePNG(surface,path.c_str()) != 0){
        SDL_Log("IMG_SavePNG Error: %s", IMG_GetError());
    }else{
        SDL_Log("Saved to %s", path.c_str());
    }

    SDL_FreeSurface(surface);



}

