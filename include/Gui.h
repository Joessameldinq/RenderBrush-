#ifndef GUI_H
#define GUI_H
#include "ToolBar.h"
#include <SDL2/SDL.h>
#include <string>
#include "Utils.h"
#include "Canvas.h"
class Gui
{
private:
    Canvas* canvas = nullptr;
    Toolbar* toolbar = nullptr;
    /**
     * Core SDL Objects
     */
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    /**
     * Window meta data
     */
    int width,height;
    std::string title;
    bool running = false;
    int fps;

    /**
     * Mouse state
     */
    int mouseX = 0, mouseY = 0;
    bool mouseDown = false;
public:
    Gui(const std::string& title,int width,int height,int fps);
    ~Gui(); //nulling allocated memory for canvas and window and renderer

    void shutdown(); //Make running = false
    void run(); //Main loop
    void handleEvents(); 
    void render(); // Draw Textures


    /**
     * Getters
     */
    SDL_Renderer* getRenderer();
    bool isRunning();
    void quit();
    /**
     * Setters
     */
    void setBrushSize(int size) { canvas->setBrushSize(size); }
    void setColor(SDL_Color color) { canvas->setColor(color); }
};
#endif

