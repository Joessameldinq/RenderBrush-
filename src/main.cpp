#include <iostream>
#include <SDL2/SDL.h>
#include "../include/Gui.h"
int main(int argc,char* argv[]){
    Gui gui("Paint",1000,1000,120);
    gui.run();
}