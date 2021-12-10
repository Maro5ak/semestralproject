#ifndef BOARD
#define BOARD
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum{
    D_UP = 0,
    D_DOWN = 1,
    D_RIGHT = 2,
    D_LEFT = 3
} Direction;

typedef struct {
    int pos[2];
    int value;
    int color[3];
    bool canMerge;
} Square;

typedef struct{
    Square *squares;
    int numOfSquares;
} Squares;


typedef struct {
    int x;
    int y;
    bool free;
} BoardPiece;

typedef struct {
    BoardPiece **grid;
    int rows;
    int columns;
} Grid;

void generateGrid(Grid *grid, const int x, const int y);

void addPiece(Grid *self, const BoardPiece piece, const int x, const int y);

void addSquare(Squares *arr, Square square);

void printSquares(Squares *sqrs);

void printGrid(Grid *self, Squares *arr);

void assignCords(Grid *self);

void spawnSquare(Grid *self, Squares *arr);

int init();

void handleInput(Direction dir, Grid *grid, Squares *sqrs);

#endif