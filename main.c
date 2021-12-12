#include "game.h"
#include "utils.h"

int main(int argc, char const *argv[]){
    int *args = parseArgs(argc, argv);
    if(args != NULL){
        if (init(args) == 1) return 1;
    }
    free(args);

    return 0;
}