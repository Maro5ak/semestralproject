#include "game.h"

bool checkFree(Grid *grid, const int x, const int y){
    return grid->grid[x][y].free;
}

bool checkBound(Grid *grid, const int x, const int y){
    return x != grid->rows && y != grid->columns && x != -1 && y != -1;
}

void sortRowUp(Squares *sqrs){
    for(int x = 0; x < sqrs->numOfSquares; x++){
        for(int y = x+1; y < sqrs->numOfSquares; y++){
            if(sqrs->squares[x].pos[0] > sqrs->squares[y].pos[0]){
                Square temp = sqrs->squares[x];
                sqrs->squares[x] = sqrs->squares[y];
                sqrs->squares[y] = temp;
            }
        }
    }
}

void sortRowDown(Squares *sqrs){
    for(int x = 0; x < sqrs->numOfSquares; x++){
        for(int y = x+1; y < sqrs->numOfSquares; y++){
            if(sqrs->squares[x].pos[0] < sqrs->squares[y].pos[0]){
                Square temp = sqrs->squares[x];
                sqrs->squares[x] = sqrs->squares[y];
                sqrs->squares[y] = temp;
            }
        }
    }
}

void sortColLeft(Squares *sqrs){
    for(int x = 0; x < sqrs->numOfSquares; x++){
        for(int y = x+1; y < sqrs->numOfSquares; y++){
            if(sqrs->squares[x].pos[1] > sqrs->squares[y].pos[1]){
                Square temp = sqrs->squares[x];
                sqrs->squares[x] = sqrs->squares[y];
                sqrs->squares[y] = temp;
            }
        }
    }
}

void sortColRight(Squares *sqrs){
    for(int x = 0; x < sqrs->numOfSquares; x++){
        for(int y = x+1; y < sqrs->numOfSquares; y++){
            if(sqrs->squares[x].pos[1] < sqrs->squares[y].pos[1]){
                Square temp = sqrs->squares[x];
                sqrs->squares[x] = sqrs->squares[y];
                sqrs->squares[y] = temp;
            }
        }
    }
}

void removeSquare(Squares *sqrs, int index){
    printf("\n\n\nBefore move: \n");
    printSquares(sqrs);
    for(int i = index; i < sqrs->numOfSquares; i++){
        sqrs->squares[i] = sqrs->squares[i+1];
    }
    sqrs->numOfSquares -= 1;
    printf("Move left:\n");
    printSquares(sqrs);
}

int checkNeighbor(Square sq, Squares *sqrs, const int x, const int y){
    for(int i = 0; i < sqrs->numOfSquares; i++){
        if(sqrs->squares[i].pos[0] == x && sqrs->squares[i].pos[1] == y){
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

void moveBoard(Grid *grid, Squares *sqrs, int x, int y){
    resetMerge(sqrs);
    int i = 0;
    while(i < sqrs->numOfSquares){    
        int tmpRow = sqrs->squares[i].pos[0]+x, tmpCol = sqrs->squares[i].pos[1]+y;
        while(checkBound(grid, tmpRow, tmpCol)){
            int merge = checkNeighbor(sqrs->squares[i], sqrs, tmpRow, tmpCol);
            if(checkFree(grid, tmpRow, tmpCol)){
                sqrs->squares[i].pos[0] = tmpRow;
                sqrs->squares[i].pos[1] = tmpCol;
                grid->grid[tmpRow][tmpCol].free = false;
                grid->grid[tmpRow-x][tmpCol-y].free = true;
                tmpRow += x;
                tmpCol += y;
            }
            
            else if(merge != -1) {
                printf("Merge [%d] with [%d]\n", i, merge);
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
        printf("Iteration: %d\n", i);
        i++;
    }    
}


void gameloop(Grid *grid, Squares *sqrs){
    char dir;
    while(1){
        scanf(" %c", &dir);
        switch(dir){
            case 'w':
                sortRowUp(sqrs);
                 printf("After sort: \n");
                printSquares(sqrs);
                moveBoard(grid, sqrs, -1, 0);
                break;
            case 'a':
                sortColLeft(sqrs);
                printf("After sort: \n");
                printSquares(sqrs);
                moveBoard(grid, sqrs, 0, -1);
                break;
            case 'd':
                sortColRight(sqrs);
                 printf("After sort: \n");
                printSquares(sqrs);
                moveBoard(grid, sqrs, 0, 1);
                break;
            case 's':
                sortRowDown(sqrs);
                printf("After sort: \n");
                printSquares(sqrs);
                moveBoard(grid, sqrs, 1, 0);
                break;
            default:
                fprintf(stderr, "Wrong input");
                break;
        }
        
        printf("Before spawn: \n");
        printSquares(sqrs);
        spawnSquare(grid, sqrs);
        printf("After spawn: \n");
        printSquares(sqrs);
        printGrid(grid, sqrs);
    }
}


void init(){
    srand(time(0));
    int x = 4;
    int y = 4;
    Grid *board;
    Squares *squares;
    board = malloc(sizeof(Grid));
    squares = malloc(sizeof(Square));
    squares->squares = malloc(x * y * sizeof(Square));

    generateGrid(board, x, y);
    assignCords(board);
    squares->numOfSquares = 0;
    spawnSquare(board, squares);
    spawnSquare(board, squares);
    printGrid(board, squares);
    gameloop(board, squares);
}
