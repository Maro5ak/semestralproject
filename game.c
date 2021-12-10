#include "game.h"
#include "renderer.h"

bool checkFree(Grid *grid, const int r, const int c){
    return grid->grid[r][c].free;
}

bool checkBound(Grid *grid, const int r, const int c){
    return r != grid->rows && c != grid->columns && r != -1 && c != -1;
}

void sortRowUp(Squares *sqrs){
    for(int r = 0; r < sqrs->numOfSquares; r++){
        for(int c = r+1; c < sqrs->numOfSquares; c++){
            if(sqrs->squares[r].pos[0] > sqrs->squares[c].pos[0]){
                Square temp = sqrs->squares[r];
                sqrs->squares[r] = sqrs->squares[c];
                sqrs->squares[c] = temp;
            }
        }
    }
}

void sortRowDown(Squares *sqrs){
    for(int r = 0; r < sqrs->numOfSquares; r++){
        for(int c = r+1; c < sqrs->numOfSquares; c++){
            if(sqrs->squares[r].pos[0] < sqrs->squares[c].pos[0]){
                Square temp = sqrs->squares[r];
                sqrs->squares[r] = sqrs->squares[c];
                sqrs->squares[c] = temp;
            }
        }
    }
}

void sortColLeft(Squares *sqrs){
    for(int r = 0; r < sqrs->numOfSquares; r++){
        for(int c = r+1; c < sqrs->numOfSquares; c++){
            if(sqrs->squares[r].pos[1] > sqrs->squares[c].pos[1]){
                Square temp = sqrs->squares[r];
                sqrs->squares[r] = sqrs->squares[c];
                sqrs->squares[c] = temp;
            }
        }
    }
}

void sortColRight(Squares *sqrs){
    for(int r = 0; r < sqrs->numOfSquares; r++){
        for(int c = r+1; c < sqrs->numOfSquares; c++){
            if(sqrs->squares[r].pos[1] < sqrs->squares[c].pos[1]){
                Square temp = sqrs->squares[r];
                sqrs->squares[r] = sqrs->squares[c];
                sqrs->squares[c] = temp;
            }
        }
    }
}

void removeSquare(Squares *sqrs, int inder){
    //printf("\n\n\nBefore move: \n");
    //printSquares(sqrs);
    for(int i = inder; i < sqrs->numOfSquares; i++){
        sqrs->squares[i] = sqrs->squares[i+1];
    }
    sqrs->numOfSquares -= 1;
    //printf("Move left:\n");
    //printSquares(sqrs);
}

int checkNeighbor(Square sq, Squares *sqrs, const int r, const int c){
    for(int i = 0; i < sqrs->numOfSquares; i++){
        if(sqrs->squares[i].pos[0] == r && sqrs->squares[i].pos[1] == c){
            if(sqrs->squares[i].value == sq.value) {
                if(sq.canMerge && sqrs->squares[i].canMerge)
                    return i;
            }
        }
    }
    return -1;
}

void resetMerge(Squares *sqrs){
    for(int i = 0; i < sqrs->numOfSquares; i++){
        sqrs->squares[i].canMerge = true;
    }
}

void movegrid(Grid *grid, Squares *sqrs, int r, int c){
    resetMerge(sqrs);
    int i = 0;
    while(i < sqrs->numOfSquares){    
        int tmpRow = sqrs->squares[i].pos[0]+r, tmpCol = sqrs->squares[i].pos[1]+c;
        while(checkBound(grid, tmpRow, tmpCol)){
            int merge = checkNeighbor(sqrs->squares[i], sqrs, tmpRow, tmpCol);
            if(checkFree(grid, tmpRow, tmpCol)){
                sqrs->squares[i].pos[0] = tmpRow;
                sqrs->squares[i].pos[1] = tmpCol;
                grid->grid[tmpRow][tmpCol].free = false;
                grid->grid[tmpRow-r][tmpCol-c].free = true;
                tmpRow += r;
                tmpCol += c;
            }
            
            else if(merge != -1) {
                //printf("Merge [%d] with [%d]\n", i, merge);
                sqrs->squares[i].value *= 2;
                sqrs->squares[i].canMerge = false;
                removeSquare(sqrs, merge);
                grid->grid[tmpRow][tmpCol].free = true;
                i -= 1;
            }
            else {
                break;
            }
        }
        //printf("Iteration: %d\n", i);
        i++;
    }    
}

void handleInput(Direction dir, Grid *grid, Squares *sqrs){
    switch(dir){
            case D_UP:
                sortRowUp(sqrs);
                movegrid(grid, sqrs, -1, 0);
                break;
            case D_LEFT:
                sortColLeft(sqrs);
                movegrid(grid, sqrs, 0, -1);
                break;
            case D_RIGHT:
                sortColRight(sqrs);
                movegrid(grid, sqrs, 0, 1);
                break;
            case D_DOWN:
                sortRowDown(sqrs);
                movegrid(grid, sqrs, 1, 0);
                break;
            default:
                fprintf(stderr, "Wrong input");
                break;
        }
    spawnSquare(grid, sqrs);
}

int gameloop(Grid *grid, Squares *sqrs){
    openWindow(grid, sqrs);
    char dir;
    /*while(1){
        scanf(" %c", &dir);
        switch(dir){
            case 'w':
                sortRowUp(sqrs);
                movegrid(grid, sqrs, -1, 0);
                break;
            case 'a':
                sortColLeft(sqrs);
                movegrid(grid, sqrs, 0, -1);
                break;
            case 'd':
                sortColRight(sqrs);
                movegrid(grid, sqrs, 0, 1);
                break;
            case 's':
                sortRowDown(sqrs);
                movegrid(grid, sqrs, 1, 0);
                break;
            default:
                fprintf(stderr, "Wrong input");
                break;
        }
        
        spawnSquare(grid, sqrs);
        scstem("clear");
        printGrid(grid, sqrs);
    }*/
    return 0;
}


int init(){
    srand(time(0));
    int r = 4;
    int c = 4;
    Grid *grid;
    Squares *squares;
    grid = malloc(sizeof(Grid));
    squares = malloc(sizeof(Square));
    squares->squares = malloc(r * c * sizeof(Square));

    generateGrid(grid, r, c);
    assignCords(grid);
    squares->numOfSquares = 0;
    spawnSquare(grid, squares);
    spawnSquare(grid, squares);
    printGrid(grid, squares);
    //gameloop(grid, squares);
    openWindow(grid, squares);

    return 0;
}
