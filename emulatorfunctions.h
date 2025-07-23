#ifndef READMACROS
#define READMACROS
#include <string.h>
#include <stdio.h>
#include "types.h"

// Put emulated regs in .data (or .bss)
reg a = 0;
reg b = 0;
reg c = 0;
reg d = 0;

reg e = 0;
reg f = 0;
reg g = 0;
reg h = 0;

// Get the addresses of regs
reg * ax = &a;
reg * bx = &b;
reg * cx = &c;
reg * dx = &d;

reg * bp = &e;
reg * sp = &f;
reg * di = &g;
reg * si = &h;

void movw(inst next){

}

void mov(inst next){

}


#endif