#include "game.h"
#include "renderer.h"

void drawGrid(WindowDetails windowd, SDL_Renderer *renderer){
    SDL_Rect gridPiece = {
        .h = 150,
        .w = 150
    };
    for(int x = 1; x < (windowd.height-2)/100; x++){
        for(int y = 1; y < (windowd.width-2)/100; y++){
            gridPiece.x = (x*100);
            gridPiece.y = (y*100);
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
            SDL_RenderFillRect(renderer, &gridPiece);
            y += 1;
        }
        x += 1;
    }
}

int openWindow(){
    
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    bool quit = false;

    WindowDetails windowd = {
        .window = window,
        .height = 1000,
        .width = 800
    };

    SDL_Init(SDL_INIT_VIDEO);
   

    window = SDL_CreateWindow(
        "2048",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowd.width,
        windowd.height,
        SDL_WINDOW_SHOWN
    );

    if(window == NULL){
        fprintf(stderr, "Couldn't open SDL Window.\n");
        return 1;
    }
    //CREATE RENDERER
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        fprintf(stderr, "Couldn't create Renderer.\n");
        return 1;
    }
    
    //MAIN LOOP
    while(!quit){
        while(SDL_PollEvent(&e) != 0){
            if(e.type == SDL_QUIT){
                quit = true;
            }        
            
            SDL_SetRenderDrawColor(renderer, 199, 195, 195, 0xFF);
            SDL_RenderClear(renderer);
            
            drawGrid(windowd, renderer);

            SDL_Rect gridPiece = {
                .h = 50,
                .w = 50,
                .x = 10,
                .y = 10
            };
            
            


            //Update screen
            SDL_RenderPresent(renderer);

        }
    }
    

    //Cleanup; function throws seg fault, dunno why, screw it
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
    
}