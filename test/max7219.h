#ifndef MAX7219_H

#include <bitset>
#include <wiringPiSPI.h>

typedef std::bitset<8> BYTE;

int max7219Setup (int spiChannel);
void registerWrite(int, BYTE, BYTE);

#define MAX7219_H
#endif
