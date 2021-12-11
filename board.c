#include "game.h"   

int getRandom(const int max){
    return rand() % max;
}

int getRandomValue(){
    return rand() % 10 ? 2 : 4;
}


void generateGrid(Grid *grid, const int x, const int y){
    grid->rows = x;
    grid->columns = y;
    grid->grid = (BoardPiece**)malloc(x * sizeof(BoardPiece*));
    for(int i = 0; i < x; i++){
        grid->grid[i] = (BoardPiece*)malloc(y * sizeof(BoardPiece));
    }
}

void addPiece(Grid* grid, const BoardPiece piece, const int x, const int y){
    grid->grid[x][y] = piece;
}
/*
bool printSquare(Squares *sqrs, int x, int y){
    for(int i = 0; i < sqrs->numOfSquares; i++) {
        if(sqrs->squares[i].pos[0] == x && sqrs->squares[i].pos[1] == y){
            printf("[ %d ]", sqrs->squares[i].value);
            return true;
        }
    }
    return false;
}
*/
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
/*
void printGrid(Grid *grid, Squares *sqrs){
    for(int i = 0; i < grid->rows; i++){
        for(int j = 0; j < grid->columns; j++){
            if(!printSquare(sqrs, i, j)) if(grid->grid[i][j].free) printf("[ T ]"); else printf("[ F ]");
        }
        printf("\n");
    }
}*/

void addSquare(Squares *sqrs, Square square){
    sqrs->numOfSquares += 1;
    sqrs->squares = realloc(sqrs->squares, sqrs->numOfSquares * sizeof(Square));
    sqrs->squares[sqrs->numOfSquares-1] = square;
}
/*
void printSquares(Squares *sqrs){
    for(int i = 0; i < sqrs->numOfSquares; i++){
        printf("[%d] -> pos[%d,%d]= %d\n", i, sqrs->squares[i].pos[0], sqrs->squares[i].pos[1], sqrs->squares[i].value);
    }
}
*/
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