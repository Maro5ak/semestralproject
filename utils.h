#ifndef UTILS
#define UTILS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static char *formatting = "[-s] [intxint]";
static char *maxsize = "number between 2 and 30";

char *concatStrings(char *str1, char *str2);

int *parseArgs(const int count, char const *args[]);

double calculateOffset(double max, double n, double x, double p);

int calculateMaxSize(double x, double space, double size);

char *intToString(int i);

#endif