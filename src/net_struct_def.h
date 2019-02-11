#ifndef NET_STRUCT_DEF_H

#include <array>

typedef struct {
	short fsensorF;
	short fsensorB;
	short fsensorL;
	short fsensorR;
	short rsensorF;
	short rsensorBL;
	short rsensorBR;
	short pmF;
	short pmB;
	short pmL;
	short pmR;
	short globalInh;
	short FInh;
	short BLInh;
	short BRInh;
	short motorF;
	short motorB;
	short motorL;
    short motorR;
}NetStruct;

/*Matrix Usage*/
//
//---------------------
//    0 1 2 3 4 5 6 7 |
//  0 x x o o o x x x |
//  1 x x x o o x x x |
//  2 x x x x x x x x |
//  3 x x x x x x o o |
//  4 o o x o x x x o |
//  5 o x x x x x x x |
//  6 x o x x o x o x |
//  7 o x x o o x x o |
//---------------------

const std::array<unsigned char, 8> defaultMatrixConfig
{
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

#define NET_STRUCT_DEF_H
#endif
