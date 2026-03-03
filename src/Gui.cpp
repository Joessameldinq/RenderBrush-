#include "../include/Gui.h"


Gui::Gui(const std::string& title,int width,int height,int fps)
    :title(title),width(width),height(height),fps(fps)
{
 

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
                SDL_Log("SDL_Init Error: %s", SDL_GetError());
                return;
    }

    this->window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_SHOWN
    );
    if (!window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        return;
    }
    this->renderer = SDL_CreateRenderer(
            this->window,
            -1,
            SDL_RENDERER_ACCELERATED
    );
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        return;
    }

    canvas   = new Canvas(renderer, width, height);
    toolbar = new Toolbar(renderer,canvas,(Point){1,1},width*0.60,height/10);
    running = true;
}

Gui::~Gui(){
    delete canvas;
    if(renderer) SDL_DestroyRenderer(renderer);
    if(window) SDL_DestroyWindow(window);
    SDL_Quit();
}


void Gui::handleEvents(){
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            running = false;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                if(mouseY < toolbar->getHeight()){
                    toolbar->handleClick({mouseX,mouseY});
                }
                else{
                    canvas->onMouseDown(mouseX,mouseY);
                }
                mouseDown = true;
            }
            break;
        case SDL_MOUSEMOTION:
            canvas->onMouseMove(event.motion.x,event.motion.y);
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT){
                mouseDown = false;
                canvas->onMouseUp();
            }
            break;
        case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE: running = false;  break;  // quit
                    case SDLK_c:      canvas->clear();  break;  // clear canvas
                    case SDLK_s: canvas->save("savings/RenderBrush_output.png"); break;
                    case SDLK_e: toolbar->toogleEraser(); break;
                }
                break;
        default:
            break;
        }
    }
    
}
void Gui::render(){
    // 1. Clear Screen
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);

    //2. draw canvas
    canvas->render();
    toolbar->render();

    SDL_RenderPresent(renderer);
}
void Gui::run(){
    while(running){
        handleEvents();
        render();
        SDL_Delay(1000/fps); // 60 fps = 1000 / 60
    }
    shutdown();
}

void Gui::shutdown() {
    running = false;
}

SDL_Renderer* Gui::getRenderer(){
    return this->renderer;
}
bool Gui::isRunning(){
    return running;
}

bool Gui::isButtonClicked(Point click, Point buttonCorner, int width, int height) {
    return click.x >= buttonCorner.x &&
           click.x <= buttonCorner.x + width &&
           click.y >= buttonCorner.y &&
           click.y <= buttonCorner.y + height;
}
