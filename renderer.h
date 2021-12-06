#ifndef RENDERER
#define RENDERER
#include <SDL2/SDL.h>

typedef struct{
    SDL_Window *window;
    int height;
    int width;
}WindowDetails;

int openWindow();

#endif