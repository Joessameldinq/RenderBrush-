#include "../include/ToolBar.h"
#include "../include/Colors.h"

Toolbar::Toolbar(SDL_Renderer* renderer,Canvas* canvas,Point leftUpCorner, int width, int height)
                : renderer(renderer),canvas(canvas),leftUpCorner(leftUpCorner),width(width),height(height){
                    canvas->setColor(Colors::ALL[selectedColorIndex]);
                    canvas->setBrushSize(brushSize);
                    swatchSize = (width-11 *padding)/10;
                }

Point Toolbar::getSwatchPos(int index) {
    return {
        leftUpCorner.x + padding + index * (swatchSize + padding),
        leftUpCorner.y + (height - swatchSize) / 2
    };
}
void Toolbar::drawSwatch(int index, SDL_Color color) {
    Point pos = getSwatchPos(index);
    SDL_Rect rect = { pos.x, pos.y, swatchSize, swatchSize };

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    if (index == selectedColorIndex) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
    }
}
void Toolbar::render(){

    //Draw BG
    // SDL_Rect bg = {leftUpCorner.x,leftUpCorner.y,width,height};
    // SDL_SetRenderDrawColor(renderer,40,40,40,255);
    // SDL_RenderFillRect(renderer,&bg);
    int i = 0;
    for (const SDL_Color& color : Colors::ALL) {
        drawSwatch(i++,color);
    }
    drawBrushControls();
    drawEraserButton();
}
Point Toolbar::getMinusButtonPos(){
        int afterSwatches = leftUpCorner.x + padding + 10 * (swatchSize + padding) + 20;
        int sy = leftUpCorner.y + (height - swatchSize) / 2;
        return {afterSwatches,sy};
}
Point Toolbar::getDisplayBoxPos() {
    Point minus = getMinusButtonPos();
    return { minus.x + swatchSize + padding, minus.y };
}
Point Toolbar::getPlusButtonPos() {
    Point display = getDisplayBoxPos();
    return { display.x + swatchSize + padding, display.y };
}

Point Toolbar::getEraserButtonPos() {
    Point plus = getPlusButtonPos();
    return { plus.x + swatchSize + padding + 20, plus.y };
}
void Toolbar::drawEraserButton(){
    Point pos = getEraserButtonPos();
    SDL_Rect rect = { pos.x, pos.y, swatchSize, swatchSize };
    // Hightlight
    if (erasing){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    }else{
        SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    }
    SDL_RenderFillRect(renderer,&rect);
    //Draw E
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    // draw a small white square inside to indicate eraser
    SDL_Rect inner = { pos.x + 8, pos.y + 8, swatchSize - 16, swatchSize - 16 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &inner);
}

void Toolbar::drawBrushControls() {
    Point minusPos   = getMinusButtonPos();
    Point displayPos = getDisplayBoxPos();
    Point plusPos    = getPlusButtonPos();

    SDL_Rect minusRect = { minusPos.x, minusPos.y, swatchSize, swatchSize };
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &minusRect);
    int my = minusPos.y + swatchSize / 2;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer,
        minusPos.x + 5, my,
        minusPos.x + swatchSize - 5, my
    );

    SDL_Rect displayRect = { displayPos.x, displayPos.y, swatchSize, swatchSize };
    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
    SDL_RenderFillRect(renderer, &displayRect);
    int maxR    = swatchSize / 2 - 2;
    int circleR = std::min(brushSize, maxR);
    int cx = displayPos.x + swatchSize / 2;
    int cy = displayPos.y + swatchSize / 2;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int dy = -circleR; dy <= circleR; dy++)
        for (int dx = -circleR; dx <= circleR; dx++)
            if (dx*dx + dy*dy <= circleR*circleR)
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);

    SDL_Rect plusRect = { plusPos.x, plusPos.y, swatchSize, swatchSize };
    SDL_SetRenderDrawColor(renderer, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer, &plusRect);
    int pmx = plusPos.x + swatchSize / 2;
    int pmy = plusPos.y + swatchSize / 2;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, plusPos.x + 5, pmy, plusPos.x + swatchSize - 5, pmy);
    SDL_RenderDrawLine(renderer, pmx, plusPos.y + 5, pmx, plusPos.y + swatchSize - 5);
}
void Toolbar::toogleEraser(){
    erasing = erasing ^ 1;
    if(erasing){
        canvas->setColor({255, 255, 255, 255}); 
    }else{
        canvas->setColor(Colors::ALL[selectedColorIndex]);
    }
}
void Toolbar::handleClick(Point clicked){
    //Click on some color
    for(int i = 0 ; i  < 10 ;i++){
        Point pos = getSwatchPos(i);
        if(isButtonClicked(clicked,pos,swatchSize,swatchSize)){
            selectedColorIndex = i;
            canvas->setColor(Colors::ALL[i]);
            return;
        }
    }

    // - button
    if(isButtonClicked(clicked,getMinusButtonPos(),swatchSize,swatchSize)){
        brushSize = std::max(1,brushSize-1);
        canvas->setBrushSize(brushSize);
        return;
    }
    // + button
    if(isButtonClicked(clicked,getPlusButtonPos(),swatchSize,swatchSize)){
        brushSize = std::min(50,brushSize+1);
        canvas->setBrushSize(brushSize);
        return;
    }

    // Eraser
    if(isButtonClicked(clicked,getEraserButtonPos(),swatchSize,swatchSize)){
        toogleEraser();
        return;
    }
    
}

    
