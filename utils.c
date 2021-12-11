#include "utils.h"
#include <string.h>

char *concatStrings(char *str1, char *str2){
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

int tokenize(const char *input, int *args){
    int tokens[2];
    char *tempArg = calloc(strlen(input), sizeof(char*));
    strcpy(tempArg, input);
    int token = 0;
    token = atoi(strtok(tempArg, ","));
    if(token < 2 || token > 100) return 1;
    args[0] = token;
    token = atoi(strtok(NULL, "\0"));
    if(token < 2 || token > 100) return 1;
    args[1] = token;
    free(tempArg);
    return 0;
}

int *parseArgs(const int count, char const *argv[]){
    int *args = malloc(2 * sizeof(int));
    if(count < 3){
        fprintf(stderr, "Too few arguments\nExpected: %s %s\n", argv[0], formatting);
    }
    else if(count > 3){
        fprintf(stderr, "Too many arguments\nExpected: %s %s\n", argv[0], formatting);
    }
    else {
        if(argv[1][0] == '-'){
            if(argv[1][1] == 's'){
                if(argv[2][strlen(argv[2]) - 1] == ',' || strlen(argv[2]) < 3) {
                    fprintf(stderr, "Invalid format.\nExpected: %s %s\n", argv[0], formatting);
                }
                else if(tokenize(argv[2], args) == 1) {
                    fprintf(stderr, "Invalid size.\nExpected: %s\n", maxsize);
                }
                else{
                    return args;
                }
            }
            else{
                fprintf(stderr, "Invalid argument.\nExpected: %s %s\n", argv[0], formatting);
            }
            
        }
        else{
            fprintf(stderr, "Wrong argument.\nExpected: %s %s\n", argv[0], formatting);
        }
    }
    free(args);
    return NULL;
}

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