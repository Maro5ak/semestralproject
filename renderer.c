#include "game.h"
#include "renderer.h"
#include "utils.h"

//Function that draws the score on the top of the screen. 
int drawScore(WindowDetails windowd, SDL_Renderer *renderer, TTF_Font *font, int score){
    SDL_Surface *textSurface;
    char *scoreText = intToString(score);
    char *fullScoreText = concatStrings("Score: ", scoreText);
    int width = strlen(fullScoreText);
    SDL_Color black = {0,0,0,0};
    textSurface = TTF_RenderText_Solid(font, fullScoreText, black);
    if(textSurface == NULL){
        fprintf(stderr, "Couldn't create surface\n");
        return 1;
    }
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL){
        fprintf(stderr, "Couldn't create texture\n");
        return 1;
    }
    SDL_Rect textBox = {
        .h = 75,
        .w = (25 * width) + (200 / width),
        .x = 100,
        .y = 10
    };
    
    SDL_RenderCopy(renderer, text, NULL, &textBox);
    free(fullScoreText);
    free(scoreText);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);

    return 0;
}

//Function to draw the game over or win text on the right
int drawGameOverText(SDL_Renderer *renderer, TTF_Font *font, char *text){
    SDL_Surface *textSurface;
    SDL_Color black = {0,0,0,0};
    textSurface = TTF_RenderText_Solid(font, text, black);
    if(textSurface == NULL){
        fprintf(stderr, "Couldn't create surface\n");
        return 1;
    }
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL){
        fprintf(stderr, "Couldn't create texture\n");
        return 1;
    }
    SDL_Rect textBox = {
        .h = 75,
        .w = (25 * 10) + (200 / 10),
        .x = 500,
        .y = 10
    };
    
    SDL_RenderCopy(renderer, text, NULL, &textBox);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);

    return 0;
}

//Function that draws the values inside the tiles. Dynamic size of the text and centered
int drawValue(SDL_Renderer *renderer, SDL_Rect square, TTF_Font *font, int value){
    SDL_Surface *textSurface;
    char *squareValue = intToString(value);
    int textWidth = strlen(squareValue);
    SDL_Color textColor = {255,255,255,0};
    if(value == 2 || value == 4) {
        textColor.r = 0;
        textColor.g = 0;
        textColor.b = 0;
        textColor.a = 0;
    }
    textSurface = TTF_RenderText_Solid(font, squareValue, textColor);
    if(textSurface == NULL){
        fprintf(stderr, "Couldn't create surface\n");
        return 1;
    }
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    if(text == NULL){
        fprintf(stderr, "Couldn't create texture\n");
        return 1;
    }
    int offsetH, offsetV;
    offsetH = calculateOffset(square.h, 1, square.h * 0.4, 20);
    offsetV = calculateOffset(square.w, 1, square.w * (0.2 * textWidth), 20);
    SDL_Rect textBox = {
        .h = square.h * 0.4,
        .w = square.w * (0.2 * textWidth),
        .x = square.x + offsetV,
        .y = square.y + offsetH
    };
    
    SDL_RenderCopy(renderer, text, NULL, &textBox);

    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(text);
    free(squareValue);
    return 0;
}

//Function that draws the grid. Dynamic tile sizes depending on the number of them
int drawGrid(WindowDetails windowd, SDL_Renderer *renderer, Grid *grid){
    double guideSize = grid->columns >= grid->rows ? grid->columns : grid->rows;
    double space = 10;
    
    SDL_Rect gridPiece = {
        .h = calculateMaxSize((double)(windowd.height - 100), space, guideSize),
        .w = calculateMaxSize((double)(windowd.width), space, guideSize)
    };
    
    double offset;
    offset = calculateOffset((double)windowd.width, (double)grid->columns, (double)gridPiece.w, space);
    for(int r = 0; r < grid->rows; r++){
        for(int c = 0; c < grid->columns; c++){
            gridPiece.x  = (c*(gridPiece.w / space)) + (c * gridPiece.w) + offset;
            gridPiece.y = (r*(gridPiece.h / space)) + (r * gridPiece.h) + 100;
            SDL_SetRenderDrawColor(renderer, 0xac, 0xac, 0xac, 0xFF);
            SDL_RenderFillRect(renderer, &gridPiece);
        }
    }
    return 0;
}

//Function that draws the tiles with values and their correct assigned colors.
int drawSquares(WindowDetails windowd, SDL_Renderer *renderer, Squares *sqrs, Grid *grid, TTF_Font *font){
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
        SDL_SetRenderDrawColor(renderer, sqrs->squares[num].color.r, sqrs->squares[num].color.g, sqrs->squares[num].color.b, 0xFF);
        SDL_RenderFillRect(renderer, &square);

       
        if (drawValue(renderer, square, font, sqrs->squares[num].value) == 1) return 1;
    }
    return 0;
}

//Function that handles opening SDL window, creating Renderer, loading Font and linking the game logic with the rendering
int openWindow(Grid *grid, Squares *sqrs){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event e;
    TTF_Font *font = NULL;
    bool quit = false;

    WindowDetails windowd = {
        .window = window,
        .height = 900,
        .width = 800
    };

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    font = TTF_OpenFont("OpenSans.ttf", 256);
    
    window = SDL_CreateWindow(
        "2048",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowd.width,
        windowd.height,
        SDL_WINDOW_SHOWN
    );

    if(font == NULL){
        fprintf(stderr, "Couldn't load font\n");
        return 1;   
    }

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
    int gameOver = 0;
    //MAIN LOOP
    while(!quit){
        
        while(SDL_PollEvent(&e) != 0){
            
            if(e.type == SDL_QUIT){
                quit = true;
            } 
            else if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:  
                        gameOver = handleInput(D_UP, grid, sqrs);
                        break;
                    case SDLK_DOWN:
                        gameOver = handleInput(D_DOWN, grid, sqrs);
                        break;
                    case SDLK_RIGHT:
                        gameOver = handleInput(D_RIGHT, grid, sqrs);
                        break;
                    case SDLK_LEFT:
                        gameOver = handleInput(D_LEFT, grid, sqrs);
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                }    
            }   
            
            
            SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
            SDL_RenderClear(renderer);
            if (drawGrid(windowd, renderer, grid) == 1) {
                fprintf(stderr, "Couldn't print grid\n");
                return 1;
            }
            if (drawSquares(windowd,renderer, sqrs, grid, font) == 1) {
                fprintf(stderr, "Couldn't draw squares\n");
                return 1;
            }
            if(drawScore(windowd, renderer, font, sqrs->score) == 1){
                fprintf(stderr, "Couldn't draw score\n");
                return 1;
            }
            if(gameOver == 1){
                if(drawGameOverText(renderer, font, "Game Over!") == 1){
                    fprintf(stderr, "Couldn't draw gameover\n");
                    return 1;
                }
            }
            if(gameOver == 2){
                if(drawGameOverText(renderer, font, "You Win!") == 1){
                    fprintf(stderr, "Couldn't draw gameover\n");
                    return 1;
                }
            }
            
            //Update screen
            SDL_RenderPresent(renderer);

        }

    }
    

    //Cleanup; function throws seg fault, dunno why
    //also address sanitizer is freaking out with SDL2 libs. Shouldn't be the biggest of problems tho
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
    
}