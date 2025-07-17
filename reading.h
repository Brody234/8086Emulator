#ifndef READING8086
#define READING8086

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "disassemblyfunctions.h"


void run(FILE *input){
    // Opcode is technically whole first byte, including first byte args
    fseek(input, 0, SEEK_END);
    long fsize = ftell(input);
    rewind(input);

    unsigned char *data = malloc(fsize);
    fread(data, 1, fsize, input);
    fclose(input);

    for(size_t i = 0; i < fsize; i++){
        inst opcode = data[i];
        if(opcode&sbit7){

            if(opcode&sbit6){
            }
            else{
                if(opcode&sbit5){

                }
                else{
                    if(opcode&sbit4){
                        
                    }
                    else{
                        if(opcode&sbit3){
                        if(opcode&sbit2){

                        }
                        // MOV DW
                        else{
                            i++;
                            inst nextbyte = data[i];
                            
                            if(opcode&sbit1){

                            }
                            else{
                                // Move 16 bytes
                                if(opcode&sbit0){
                                    movw(nextbyte);
                                }
                                // Move 8 bytes
                                else{
                                    mov(nextbyte);
                                }
                            }
                                
                            }
                        }
                        else{

                        }
                    }
                }
            }
        }
        else{

        }
    }
}


#endif