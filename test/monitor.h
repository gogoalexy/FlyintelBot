#ifndef MONITOR_H

#include <array>
#include <cstring>
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
    NeuroMonitor(int, int, int);
    void init();
    void refresh();
    void recordActivity(int, int, bool);
    void updateMatrix();

private:
    const std::array<BYTE, 8> defaultMatrixConfig;
    std::array<BYTE, 8> matrixConfig;
    max7219 chip;
};

#define MONITOR_H
#endif
