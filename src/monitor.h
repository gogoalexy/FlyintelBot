#ifndef MONITOR_H

#include <array>
#include <cstring>
//#include "net_struct_def.h"
#include "max7219.h"

class NeuroMonitor
{
public:
    NeuroMonitor(int, int);
    void init();
    void refresh();
    void recordActivity(int, int);
    void updateMatrix();

private:
    const std::array<BYTE, 8> defaultMatrixConfig;
    std::array<BYTE, 8> matrixConfig;
    max7219 chip;
};

#define MONITOR_H
#endif
