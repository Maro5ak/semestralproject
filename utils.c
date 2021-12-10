#include "utils.h"

double calculateOffset(double maxSize, double n, double x, double p){
    return (maxSize - (n * x + (n - 1) * (x / p))) / 2;
}

int calculateMaxSize(double x, double space, double size){
    return (int)((space * x) / (size * space + (size + 1)));   
}

char *intToString(int i){
    char *num = malloc(8 * sizeof(char));
    sprintf(num, "%d", i);
    return num;
}