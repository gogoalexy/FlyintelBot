#ifndef MONITOR_H

#include <cstring>
#include "max7219.h"


class LEDmatrix {
public:
LEDmatrix();
bool init();
void LEDwrite(unsigned short, unsigned char);
void setBrightness();
void setMode();

private:


};
