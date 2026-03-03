#include "../include/ToolBar.h"
#include "../include/Colors.h"

Toolbar::Toolbar(SDL_Renderer* renderer,Canvas* canvas,Point leftUpCorner, int width, int height)
                : renderer(renderer),canvas(canvas),leftUpCorner(leftUpCorner),width(width),height(height){
                    canvas->setColor(Colors::ALL[selectedColorIndex]);
                    canvas->setBrushSize(brushSize);
                    swatchSize = (width-11 *padding)/10;
                }
void Toolbar::drawSwatch(int index, SDL_Color color) {
    int sx = leftUpCorner.x + padding + index * (swatchSize + padding);
    int sy = leftUpCorner.y + (height - swatchSize) / 2;  // centered
    SDL_Rect rect = { sx, sy, swatchSize, swatchSize };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    if (index == selectedColorIndex) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
void Toolbar::render(){

    //Draw BG
    SDL_Rect bg = {leftUpCorner.x,leftUpCorner.y,width,height};
    SDL_SetRenderDrawColor(renderer,40,40,40,255);
    SDL_RenderFillRect(renderer,&bg);
    int i = 0;
    for (const SDL_Color& color : Colors::ALL) {
        drawSwatch(i++,color);
    }
}

    
