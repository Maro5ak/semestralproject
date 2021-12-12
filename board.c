#include "game.h"   

//Get a random number upper bound
int getRandom(const int max){
    return rand() % max;
}

//Get a random number of either 2 or 4
int getRandomValue(){
    return rand() % 10 ? 2 : 4;
}

//Function that generates a grid based on the input values, grid is a 2D array of BoardPieces
void generateGrid(Grid *grid, const int x, const int y){
    grid->rows = x;
    grid->columns = y;
    grid->grid = (BoardPiece**)malloc(x * sizeof(BoardPiece*));
    for(int i = 0; i < x; i++){
        grid->grid[i] = (BoardPiece*)malloc(y * sizeof(BoardPiece));
    }
}

//Adding a piece to the grid
void addPiece(Grid* grid, const BoardPiece piece, const int x, const int y){
    grid->grid[x][y] = piece;
}

//Function to assign 2D coordinates to each grid tile. The grid is a 2D array of BoardPieces
void assignCords(Grid *grid){
    BoardPiece pc;
    for(int i = 0; i < grid->rows; i++){
        for(int j = 0; j < grid->columns; j++){
            pc.x = i;
            pc.y = j;
            pc.free = true;
            addPiece(grid, pc, i, j);
        }
    }
}

//Function to add a square to the array of squares and update the size of the array
void addSquare(Squares *sqrs, Square square){
    sqrs->numOfSquares += 1;
    sqrs->squares = realloc(sqrs->squares, sqrs->numOfSquares * sizeof(Square));
    sqrs->squares[sqrs->numOfSquares-1] = square;
}
//Function that spawns new squares to a free space on the grid, assigns it a random value of 2 or 4 and a color based on the value
void spawnSquare(Grid *grid, Squares *sqrs){
    Square sq;

    while(1){
        int x = getRandom(grid->rows);
        int y = getRandom(grid->columns);
        if(grid->grid[x][y].free){
            sq.pos[0] = x;
            sq.pos[1] = y;  
            sq.value = getRandomValue();
            sq.color = colorDict(sqrs, sq);
            addSquare(sqrs, sq);
            grid->grid[x][y].free = false;
            break;
        }
    }
}