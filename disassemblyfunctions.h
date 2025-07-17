#ifndef READMACROS
#define READMACROS
#include <string.h>
#include <stdio.h>
#include "types.h"

/* 
 * Note before I even start writing this: 
 * This file is gonna use strcpy and strcat A LOT 
 * so there will be exploits created here,
 * they will be disassembler exploits not VM breaks.
 * This file should not be included in ANY VM related files.
 * Or I just didn't finish the project and they're nothing lol.
 */

static const char *reg8names[8]  = {"AL","CL","DL","BL","AH","CH","DH","BH"};
static const char *reg16names[8] = {"AX","CX","DX","BX","SP","BP","SI","DI"};

static const char *reg8namescs[8]  = {"AL, ","CL, ","DL, ","BL, ","AH, ","CH, ","DH, ","BH, "};
static const char *reg16namescs[8] = {"AX, ","CX, ","DX, ","BX, ","SP, ","BP, ","SI, ","DI, "};

#define reg8f(x) (reg8namescs[x])
#define reg16f(x) (reg16namescs[x])
#define reg8s(x) (reg8names[x])
#define reg16s(x) (reg16names[x])

FILE *output;

void setdest(const char* filepath){
    output = fopen(filepath, "wb");
    if(!output){
        fprintf(stderr, "Unable to open a new asm file.\n");
    }
}

void enddest(){
    fclose(output);
}

void movw(inst next){
    char dest[12] = "MOV ";
    strcat(dest, reg16f(low_reg_id(next)));
    strcat(dest, reg16s(mid_reg_id(next)));
    dest[10] = '\n';
    printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, 11, output);
}

void mov(inst next){
    char dest[12] = "MOV ";
    strcat(dest, reg8f(low_reg_id(next)));
    strcat(dest, reg8s(mid_reg_id(next)));
    dest[10] = '\n';
    printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, 11, output);
}


#endif