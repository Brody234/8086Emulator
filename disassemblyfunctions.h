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

static const char *regMemCalcs00[8]  = {"(BX)+(SI)","(BX)+(DI)","(BP)+(SI)","(BP)+(DI)","(SI)","(DI)","(BP)","(BX)"};

#define mergeHighLow(high, low) ((word)((((word)high)<< 8) | low))

#define reg8f(x) (reg8namescs[x])
#define reg16f(x) (reg16namescs[x])
#define reg8s(x) (reg8names[x])
#define reg16s(x) (reg16names[x])

#define memreg(x) (regMemCalcs00[x])

// THIS MACRO IS FUNCTIONAL BUT UNSAFE - ChatGPT. Have a field day with it ig.
#define addCS(x) (strcat(x, ", "))

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

void movwToReg(inst next, byte low, byte high, byte mod, byte rum){
    char dest[40] = "MOV ";
    strcat(dest, reg16f(mid_reg_id(next)));
    word arrayaddr16 = mergeHighLow(high, low);
    char addr16[20];
    sprintf(addr16, "%d", arrayaddr16);
    char addr8[20];
    sprintf(addr8, "%d", low);
    //printf("%d", mod);
    if(mod == 0x0 && rum == 0x6){
        strcat(dest, addr16);
    }
    else if(mod == 0x0){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        strcat(dest, "]");
    }
    else if (mod == 0x1){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        char num[10];
        //printf("\n%d\n", low);
        sprintf(num, "+%d]", low);
        strcat(dest, num);
    }
    else if (mod == 0x2){
        strcat(dest, "[");
        addCS(dest);
        strcat(dest, memreg(rum));
        char num[20];
        sprintf(num, "+%d]", mergeHighLow(high, low));
        strcat(dest, num);
    }
    else{
        strcat(dest, reg16s(modreg_RUM(next)));
    }

    strcat(dest, "\n");
    size_t len = strlen(dest);
    //printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, len, output);
}

void movwToRM(inst next, byte low, byte high, byte mod, byte rum){
    char dest[40] = "MOV ";
    word arrayaddr16 = mergeHighLow(high, low);
    char addr16[20];
    sprintf(addr16, "%d", arrayaddr16);
    char addr8[20];
    sprintf(addr8, "%d", low);

    if(mod == 0x0 && rum == 0x6){
        strcat(dest, "[");
        strcat(dest, addr16);
        strcat(dest, "]");
    }
    else if(mod == 0x0){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        strcat(dest, "]");
    }
    else if (mod == 0x1){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        char num[10];
        sprintf(num, "+%d", low);
        strcat(dest, num);
        strcat(dest, "]");
    }
    else if (mod == 0x2){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        char num[20];
        sprintf(num, "+%d", mergeHighLow(high, low));
        strcat(dest, num);
        strcat(dest, "]");
    }
    else{
        strcat(dest, reg16s(modreg_RUM(next)));
    }
    addCS(dest);
    strcat(dest, reg16s(mod_REG_rum(next)));
    strcat(dest, "\n");
    size_t len = strlen(dest);
    printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, len, output);

}


void movToReg(inst next, byte low, byte high, byte mod, byte rum){
    /*char dest[12] = "MOV ";
    strcat(dest, reg8f(mid_reg_id(next)));
    strcat(dest, reg8s(low_reg_id(next)));
    dest[10] = '\n';
    printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, 11, output);*/
    char dest[40] = "MOV ";
    strcat(dest, reg8f(mid_reg_id(next)));
    word arrayaddr16 = mergeHighLow(high, low);
    char addr16[20];
    sprintf(addr16, "%d", arrayaddr16);
    char addr8[20];
    sprintf(addr8, "%d", low);

    if(mod == 0x0 && rum == 0x6){
        strcat(dest, "[");
        strcat(dest, addr16);
                strcat(dest, "]");

    }
    else if(mod == 0x0){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
                strcat(dest, "]");

    }
    else if (mod == 0x1){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        char num[10];
        sprintf(num, "+%d", low);
        strcat(dest, num);
                strcat(dest, "]");

    }
    else if (mod == 0x2){
                        strcat(dest, "[");

        strcat(dest, memreg(rum));
        char num[20];
        sprintf(num, "+%d", mergeHighLow(high, low));
        strcat(dest, num);
                strcat(dest, "]");

    }
    else{
        strcat(dest, reg8s(modreg_RUM(next)));

    }
    strcat(dest, "\n");
    size_t len = strlen(dest);
    //printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, len, output);

}

void movToRM(inst next, byte low, byte high, byte mod, byte rum){
    char dest[40] = "MOV ";
    word arrayaddr16 = mergeHighLow(high, low);
    char addr16[20];
    sprintf(addr16, "%d", arrayaddr16);
    char addr8[20];
    sprintf(addr8, "%d", low);

    if(mod == 0x0 && rum == 0x6){
        strcat(dest, "[");
        strcat(dest, addr16);
        strcat(dest, "]");
    }
    else if(mod == 0x0){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        printf("%s", dest);
        strcat(dest, "]");
    }
    else if (mod == 0x1){
        strcat(dest, "[");
        strcat(dest, memreg(rum));
        char num[10];
        sprintf(num, "+%d", low);
        strcat(dest, num);
        strcat(dest, "]");
    }
    else if (mod == 0x2){
        strcat(dest, "[");
        addCS(dest);
        strcat(dest, memreg(rum));
        char num[20];
        sprintf(num, "+%d", mergeHighLow(high, low));
        strcat(dest, num);
        strcat(dest, "]");
    }
    else{
        strcat(dest, reg8s(modreg_RUM(next)));
    }
    addCS(dest);
    strcat(dest, reg8s(mid_reg_id(next)));
    strcat(dest, "\n");
    size_t len = strlen(dest);
    printf("%s", dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, len, output);

}


void moveImmediateToReg0W(byte data, byte reg){
    char dest[30] = "MOV ";
    char num[20];
    strcat(dest, reg8f(reg));
    sprintf(num, "%d", data);
    strcat(dest, num);
    char newline[5] = "\n";
    strcat(dest, newline);
    size_t len = strlen(dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, len, output);

}

void movImmediateToReg1W(byte high, byte low, regid reg){
    char dest[30] = "MOV ";

    char num[20];
    strcat(dest, reg16f(reg));
    word data = (((word)high)<< 8) | low;
    sprintf(num, "%d", data);
    strcat(dest, num);
    char newline[5] = "\n";
    strcat(dest, newline);
    size_t len = strlen(dest);
    if(!output){
        fprintf(stderr, "Pick a file to open\n");
        return;
    }
    fwrite(dest, 1, len, output);
}
#endif