#ifndef TYPES8086
#define TYPES8086

#include <stdint.h>

// Types for registers, instructions
typedef uint16_t reg;
typedef uint8_t subreg;
typedef uint8_t regid;

typedef uint8_t byte;
typedef uint16_t word;

typedef uint8_t inst;


// Types for 8 bit masking, sbit as in subregister bit
typedef uint8_t mask8;
const mask8 sbit0 = 0x01;
const mask8 sbit1 = 0x02;
const mask8 sbit2 = 0x04;
const mask8 sbit3 = 0x08;
const mask8 sbit4 = 0x10;
const mask8 sbit5 = 0x20;
const mask8 sbit6 = 0x40;
const mask8 sbit7 = 0x80;


// types for 16 bit masking
typedef uint16_t mask16;
// Low
const mask16 bit0 = 0x0001;
const mask16 bit1 = 0x0002;
const mask16 bit2 = 0x0004;
const mask16 bit3 = 0x0008;
const mask16 bit4 = 0x0010;
const mask16 bit5 = 0x0020;
const mask16 bit6 = 0x0040;
const mask16 bit7 = 0x0080;
// High
const mask16 bit8 = 0x0100;
const mask16 bit9 = 0x0200;
const mask16 bit10 = 0x0400;
const mask16 bit11 = 0x0800;
const mask16 bit12 = 0x1000;
const mask16 bit13 = 0x2000;
const mask16 bit14 = 0x4000;
const mask16 bit15 = 0x8000;

// 3 bits 210 from 8 bit
#define low_reg_id(x) ((x) & 0x07)
// 3 bits 543 from 8 bit
#define mid_reg_id(x) (((x)>>3) & 0x7)

#define MOD_regrum(x) (((x)>>6) &0x3)

#define mod_REG_rum(x) (((x)>>3) &0x7)

#define modreg_RUM(x) (((x))&0x7)
#endif