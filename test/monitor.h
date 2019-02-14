#ifndef MONITOR_H

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

class NeuroMonitor : protected max7219
{
public:
    NeuroMonitor(int);
    bool isSPIinit();
    void init();
    void refresh();

    void recordActivity(int, int, bool);
    void updateMatrix();

private:
    std::array<BYTE, 8> matrixConfig;
};

#define MONITOR_H
#endif
