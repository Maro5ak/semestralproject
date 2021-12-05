#ifndef BOARD
#define BOARD
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct {
    int pos[2];
    int value;
    int color;
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

void init();

#endif