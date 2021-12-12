#include "utils.h"

//Function to concatenate two strings
char *concatStrings(char *str1, char *str2){
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

//Function to check format of arguments. Delimiter must be x while specifying size, otherwise Formatting error
int checkFormat(const char *input){
    for(int i = 0; i < (int)strlen(input); i++) {
        if(input[i] == 'x') return 0;
    }
    return 1;
}

//Function to tokenize arguments and parsing into integers to specify the size of the game grid
int tokenize(const char *input, int *args){
    int tokens[2];
    char *tempArg = calloc(strlen(input), sizeof(char*));
    
    strcpy(tempArg, input);
    int token = 0;
    token = atoi(strtok(tempArg, "x"));
    if(token < 2 || token > 100) return 1;
    args[0] = token;
    token = atoi(strtok(NULL, "\0"));
    if(token < 2 || token > 100) return 1;
    args[1] = token;

    free(tempArg);
    return 0;
}

//Function to parse arguments
//Error checks for 1. invalid formats, 2. sizes out of bounds, 3. too few or too many arguments
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
                if(argv[2][strlen(argv[2]) - 1] == 'x' || strlen(argv[2]) < 3) {
                    fprintf(stderr, "Invalid format.\nExpected: %s %s\n", argv[0], formatting);
                }
                else if(checkFormat(argv[2]) == 1){
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

//Function that calculates the offset to the center so the elements rendered are centered
double calculateOffset(double maxSize, double n, double x, double p){
    return (maxSize - (n * x + (n - 1) * (x / p))) / 2;
}

//Function that calculates max size of the grid including the spaces between each tile
int calculateMaxSize(double x, double space, double size){
    return (int)((space * x) / (size * space + (size + 1)));   
}

//Functoin that converts integer to string
char *intToString(int i){
    char *num = malloc(8 * sizeof(char));
    sprintf(num, "%d", i);
    return num;
}