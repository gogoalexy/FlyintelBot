#ifndef MONITOR_H

#include <vector>
#include <array>
#include <cstring>
#include <wiringPi.h>
#include "net_struct_def.h"
#include "max7219.h"

const std::array<BYTE, 8> defaultMatrixConfig
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

class NeuroMonitor
{
public:
    NeuroMonitor();
    int init(int, int);
    void refresh();

    void recordActivity(int, int, bool);
    void update1Matrix(int);


private:
    std::array<BYTE, 8> matrixConfig;
    max7219 Base;
    max7219 Active;
};

#define MONITOR_H
#endif
