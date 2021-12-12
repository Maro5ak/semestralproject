#ifndef GAME
#define GAME
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Enum for directions
typedef enum{
    D_UP = 0,
    D_DOWN = 1,
    D_RIGHT = 2,
    D_LEFT = 3
} Direction;

//Structure for RGB color.
typedef struct{
    int r;
    int g;
    int b;
}RGB;

//Structure for the game squares; Holds data for x and y position of the square, value of the square, color based on the value and if the square can be merged
typedef struct {
    int pos[2];
    int value;
    RGB color;
    bool canMerge;
} Square;

//Structure holding players score, all the used colors, Array of all the squares and its length
typedef struct{
    int score;
    RGB *colors;
    Square *squares;
    int numOfSquares;
} Squares;

//Structure for gridpiece holding information of its x and y position and if its free or not (that means if there's square on that position or not)
typedef struct {
    int x;
    int y;
    bool free;
} BoardPiece;

//Main grid structure, holding 2D array of pieces, num of rows and columns
typedef struct {
    BoardPiece **grid;
    int rows;
    int columns;
} Grid;

//Declaration of bunch of functions used throughout
RGB colorDict(Squares *sqrs, Square sq);

void generateGrid(Grid *grid, const int x, const int y);

void addPiece(Grid *self, const BoardPiece piece, const int x, const int y);

void addSquare(Squares *arr, Square square);

void assignCords(Grid *self);

void spawnSquare(Grid *self, Squares *arr);

int init();

int handleInput(Direction dir, Grid *grid, Squares *sqrs);

#endif