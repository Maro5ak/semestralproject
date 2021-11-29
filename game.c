#include "game.h"

bool checkFree(Grid *grid, const int x, const int y){
    return grid->grid[x][y].free;
}

bool checkBound(Grid *grid, const int x, const int y){
    return x != grid->rows && y != grid->columns && x != -1 && y != -1;
}

void reverseSquares(Squares *sqrs){
    for(int i = 1; i < sqrs->numOfSquares/2; i++){
        Square tmp = sqrs->squares[i];
        sqrs->squares[i] = sqrs->squares[(sqrs->numOfSquares-1) - i];
        sqrs->squares[(sqrs->numOfSquares-1) - i] = tmp;
    }
}

bool checkNeighbor(Square sq, Squares *sqrs, const int x, const int y, const int index){
    for(int i = 0; i < sqrs->numOfSquares; i++){
        if(sqrs->squares[i].pos[0] == x && sqrs->squares[i].pos[1] == y){
            if(sqrs->squares[i].value == sq.value) {
                return true;
            }
        }
    }
    return false;
}

void moveBoard(Grid *grid, Squares *sqrs, int x, int y){
    Square *tempArr;
    tempArr = malloc(x * y * sizeof(Square));
    for(int i = 0; i < sqrs->numOfSquares; i++){
        for(int row = 0; row < grid->rows; row++){
            for(int col = 0; col < grid->columns; col++){
                if(sqrs->squares[i].pos[0] == row && sqrs->squares[i].pos[1] == col){
                    int tmpRow = row+x, tmpCol = col+y;
                    while(checkBound(grid, tmpRow, tmpCol)){
                        if(checkFree(grid, tmpRow, tmpCol)){
                            sqrs->squares[i].pos[0] = tmpRow;
                            sqrs->squares[i].pos[1] = tmpCol;
                            grid->grid[tmpRow][tmpCol].free = false;
                            grid->grid[tmpRow-x][tmpCol-y].free = true;
                            tmpRow += x;
                            tmpCol += y;
                        }
                        else if(checkNeighbor(sqrs->squares[i], sqrs, tmpRow, tmpCol, i)) {
                            Square sq;
                            sq.pos[0] = tmpRow;
                            sq.pos[1] = tmpCol;
                            sq.value = 2 * sqrs->squares[i].value;
                            tempArr[i] = sq;
                            /*reverseSquares(sqrs);
                            sqrs->numOfSquares -= 2;*/
                            sqrs->numOfSquares -= 1;
                            grid->grid[tmpRow][tmpCol].free = true;
                        }
                        else break;
                    }
                }
            }
        }
        tempArr[i] = sqrs->squares[i];
    }
    for(int i = 0; i < sqrs->numOfSquares; i++){
        sqrs->squares[i] = tempArr[i];
    }
    
    

}


void gameloop(Grid *grid, Squares *sqrs){
    char dir;
    while(1){
        scanf(" %c", &dir);
        switch(dir){
            case 'w':
                moveBoard(grid, sqrs, -1, 0);
                break;
            case 'a':
                moveBoard(grid, sqrs, 0, -1);
                break;
            case 'd':
                moveBoard(grid, sqrs, 0, 1);
                break;
            case 's':
                moveBoard(grid, sqrs, 1, 0);
                break;
            default:
                fprintf(stderr, "Wrong input");
                break;
        }
        spawnSquare(grid, sqrs);
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
