#include "../types.h"
#include <stdio.h>
#include "../disassemblyfunctions.h"
#include "../reading.h"

int main(int argc, char *argv[]){
    if (argc != 3){
        printf("%d", argc);
        fprintf(stderr, "Pick a file to open.\n");
        return 1;
    }
    FILE *input = fopen(argv[1], "r");
    if(!input){
        fprintf(stderr, "File not found.\n");
        return -1;
    }
    
    setdest(argv[2]);

    run(input);

    enddest();

    fclose(input);
    return 0;
}