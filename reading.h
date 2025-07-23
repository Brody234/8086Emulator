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
                    if(opcode&sbit4){
                        // Immediate to register w reg data data
                        regid reg = low_reg_id(opcode);
                        if(opcode&sbit3){
                            byte high = data[i+2];
                            byte low = data[i+1];
                            i+=2;
                            movImmediateToReg1W(high, low, reg);
                        }
                        else{
                            byte ind = data[i+1];
                            i++;
                            moveImmediateToReg0W(ind, reg);
                        }
                    }
                    else{

                    }
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
                                byte mod = MOD_regrum(nextbyte);
                                byte rum = modreg_RUM(nextbyte);
                                byte dlow = data[i+1];
                                byte dhigh = data[i+2];
                                if(mod == 0x0 && rum == 0x6){
                                    i+=2;
                                }
                                if(mod == 0x1){
                                    i++;
                                }
                                if(mod == 0x2){
                                    i+=2;
                                }

                                //Move to Reg D= 1
                                if(opcode&sbit1){
                                    // Move 16 bytes
                                    if(opcode&sbit0){
                                        movwToReg(nextbyte, dlow, dhigh, mod, rum);
                                    }
                                    // Move 8 bytes
                                    else{
                                        movToReg(nextbyte, dlow, dhigh, mod, rum);
                                    }
                                }
                                // Move to R/M
                                // D=0
                                else{
                                    // Move 16 bytes
                                    if(opcode&sbit0){
                                        movwToRM(nextbyte, dlow, dhigh, mod, rum);
                                    }
                                    // Move 8 bytes
                                    else{
                                        movToRM(nextbyte, dlow, dhigh, mod, rum);
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