#include "game.h"
#include "renderer.h"

bool checkFree(Grid *grid, const int r, const int c){
    return grid->grid[r][c].free;
}

bool checkBound(Grid *grid, const int r, const int c){
    return r != grid->rows && c != grid->columns && r != -1 && c != -1;
}

bool checkBoard(Grid *grid, Squares *sqrs){
    return sqrs->numOfSquares < grid->columns * grid->rows;
}

void calculateScore(Squares *sqrs, int value){
    sqrs->score += value;
}

RGB colorDict(Squares *sqrs, Square sq){
    switch(sq.value){
        case 2:
            return sqrs->colors[0];
        case 4:
            return sqrs->colors[1];
        case 8:
            return sqrs->colors[2];
        case 16:
            return sqrs->colors[3];
        case 32:
            return sqrs->colors[4];
        case 64:
            return sqrs->colors[5];
        case 128:
            return sqrs->colors[6];
        case 256:
            return sqrs->colors[7];
        case 512:
            return sqrs->colors[8];
        case 1024:
            return sqrs->colors[9];
        case 2048:
            return sqrs->colors[10];
    }
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

void removeSquare(Squares *sqrs, int index){
    for(int i = index; i < sqrs->numOfSquares; i++){
        sqrs->squares = realloc(sqrs->squares, (sqrs->numOfSquares + 1) * sizeof(Square));
        sqrs->squares[i] = sqrs->squares[i+1];
    }
    sqrs->numOfSquares -= 1;
    sqrs->squares = realloc(sqrs->squares, sqrs->numOfSquares * sizeof(Square));

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
                calculateScore(sqrs, sqrs->squares[i].value);
                sqrs->squares[i].color = colorDict(sqrs, sqrs->squares[i]);
                sqrs->squares[i].canMerge = false;
                removeSquare(sqrs, merge);
                grid->grid[tmpRow][tmpCol].free = true;
                i -= 1;
               
            }
            else {
                break;
            }
        }
        i++;
    }    
}

int handleInput(Direction dir, Grid *grid, Squares *sqrs){
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
            fprintf(stderr, "Wrong input\n");
            break;
    }
    if(!checkBoard(grid, sqrs)) {
        return 1;
    }
    spawnSquare(grid, sqrs);
    return 0;
}

void assignColors(Squares *sqrs, int length){
    sqrs->colors = malloc(length * sizeof(RGB));
    //PAIN
    RGB two = {.r = 0xee, .g = 0xe4, .b = 0xda};
    RGB four = {.r = 0xed, .g = 0xe0, .b = 0xc8};
    RGB eight = {.r = 0xf2, .g = 0xb1, .b = 0x79};
    RGB sixteen = {.r = 0xf5, .g = 0x95, .b = 0x63};
    RGB threetwo = {.r = 0xf6, .g = 0x7c, .b = 0x60};
    RGB sixfour = {.r = 0xf6, .g = 0x5e, .b = 0x3b};
    RGB onetwoeight = {.r = 0xed, .g = 0xcf, .b = 0x73};
    RGB twofivesix = {.r = 0xed, .g = 0xcc, .b = 0x62};
    RGB fivetwelve = {.r = 0xed, .g = 0xc8, .b = 0x50};
    RGB thtwentyfour = {.r = 0xed, .g = 0xc5, .b = 0x3f};
    RGB twofoureight = {.r = 0xed, .g = 0xc2, .b = 0x2d};
    
    sqrs->colors[0] = two;
    sqrs->colors[1] = four;
    sqrs->colors[2] = eight;
    sqrs->colors[3] = sixteen;
    sqrs->colors[4] = threetwo;
    sqrs->colors[5] = sixfour;
    sqrs->colors[6] = onetwoeight;
    sqrs->colors[7] = twofivesix;
    sqrs->colors[8] = fivetwelve;
    sqrs->colors[9] = thtwentyfour;
    sqrs->colors[10] = twofoureight;
}


int init(int *args){
    srand(time(0));
    int r = args[0];
    int c = args[1];
    Grid *grid;
    Squares *squares;
    grid = malloc(sizeof(Grid));
    squares = malloc(sizeof(Squares));
    
    squares->squares = malloc(sizeof(Square)); 
    squares->score = 0;
    squares->numOfSquares = 0;

    assignColors(squares, 11);
    generateGrid(grid, r, c);
    assignCords(grid);
    spawnSquare(grid, squares);
    spawnSquare(grid, squares);
    //printGrid(grid, squares);
    //gameloop(grid, squares);
    if(openWindow(grid, squares) == 1) return 1;
    
    free(squares->colors);
    free(squares->squares);
    free(squares);
    for(int i = 0; i < grid->rows; i++){
        free(grid->grid[i]);
    }
    free(grid->grid);
    free(grid);
    return 0;
}
