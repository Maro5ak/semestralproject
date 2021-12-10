#include "game.h"
#include "renderer.h"
#include "utils.h"

void drawValue(SDL_Renderer *renderer, SDL_Rect square, char *value){
    SDL_Surface *textSurface;
    TTF_Font *font = TTF_OpenFont("OpenSans.ttf", 256);
    if(!font){
        fprintf(stderr, "No font\n");
        return;   
    }
    SDL_Color white = {255, 255, 255, 0};
    textSurface = TTF_RenderText_Solid(font, value, white);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textBox = {
        .h = square.h-50,
        .w = square.w-80,
        .x = square.x+20,
        .y = square.y + 20
    };
    
    SDL_RenderCopy(renderer, text, NULL, &textBox);

    
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
}


void drawGrid(WindowDetails windowd, SDL_Renderer *renderer, Grid *grid){
    double guideSize = grid->columns >= grid->rows ? grid->columns : grid->rows;
    double space = 10;
    
    SDL_Rect gridPiece = {
        .h = calculateMaxSize((double)(windowd.height - 100), space, guideSize),
        .w = calculateMaxSize((double)(windowd.width), space, guideSize)
    };
    
    double offset;
    //offset = (double)windowd.width - ((((double)grid->columns * (double)gridPiece.w)) + (((double)grid->columns - (double)1) * ((double)gridPiece.w / space)));
    //offset /= 2;
    offset = calculateOffset((double)windowd.width, (double)grid->columns, (double)gridPiece.w, space);
    for(int r = 0; r < grid->rows; r++){
        for(int c = 0; c < grid->columns; c++){
            gridPiece.x  = (c*(gridPiece.w / space)) + (c * gridPiece.w) + offset;
            gridPiece.y = (r*(gridPiece.h / space)) + (r * gridPiece.h) + 100;
            SDL_SetRenderDrawColor(renderer, 0xac, 0xac, 0xac, 0xFF);
            SDL_RenderFillRect(renderer, &gridPiece);
        }
    }
}

void drawSquares(WindowDetails windowd, SDL_Renderer *renderer, Squares *sqrs, Grid *grid){
    double guideSize = grid->columns >= grid->rows ? grid->columns : grid->rows;
    double space = 10;
    
    SDL_Rect square = {
        .h = calculateMaxSize((double)(windowd.height - 100), space, guideSize),
        .w = calculateMaxSize((double)(windowd.width), space, guideSize)
    };
    
    double offset;
    offset = calculateOffset((double)windowd.width, (double)grid->columns, (double)square.w, space);

    int row, col;
    for(int num = 0; num < sqrs->numOfSquares; num++){
        row = sqrs->squares[num].pos[0];
        col = sqrs->squares[num].pos[1];
        square.x = (col * (square.w / space)) + (col * square.w) + offset;
        square.y = (row * (square.h / space)) + (row * square.h) + 100;
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &square);
        drawValue(renderer, square, intToString(sqrs->squares[num].value));
    }
}

int openWindow(Grid *grid, Squares *sqrs){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    bool quit = false;

    WindowDetails windowd = {
        .window = window,
        .height = 900,
        .width = 800
    };

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

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
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:  
                        handleInput(D_UP, grid, sqrs);
                        break;
                    case SDLK_DOWN:
                        handleInput(D_DOWN, grid, sqrs);
                        break;
                    case SDLK_RIGHT:
                        handleInput(D_RIGHT, grid, sqrs);
                        break;
                    case SDLK_LEFT:
                        handleInput(D_LEFT, grid, sqrs);
                        break;
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
            }       
            
            SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
            SDL_RenderClear(renderer);
            drawGrid(windowd, renderer, grid);
            drawSquares(windowd,renderer, sqrs, grid);
            
            //Update screen
            SDL_RenderPresent(renderer);

        }
    }
    

    //Cleanup; function throws seg fault, dunno why, screw it
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return quit ? 1 : 0;
    
}