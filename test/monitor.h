#ifndef MONITOR_H

#include <cstring>
#include "max7219.h"


class LEDmatrix {
public:
LEDmatrix();
bool init();
void registerWrite(unsigned char, unsigned char);
void setBrightness();
void setMode();

private:


};

#define MAX7219_DIGIT_REG(pos)  ((pos) + 1)
#define MAX7219_COLUMN_REG(pos) MAX7219_DIGIT_REG(pos)

