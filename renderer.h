#ifndef RENDERER
#define RENDERER
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct{
    SDL_Window *window;
    int height;
    int width;
}WindowDetails;

int openWindow(Grid *grid, Squares *sqrs);

#endif