#include "monitor.h"

using namespace std;

NeuroMonitor::NeuroMonitor(int spiChannel = 1, int spiSpeed = 1000000) : 
    defaultMatrixConfig(0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000,
                        0b00000000)
{
    
    memcpy(matrixConfig.data(), defaultMatrixConfig.data(), matrixConfig.size());

    if(chip.max7219Setup(spiChannel, spiSpeed) == -1)
    {
        exit(1);
    }
}

void NeuroMonitor::init()
{        
    chip.setShutdown(EXIT_SHUTDOWN);
    chip.setDecode(BCD_DECODE_NONE);
    chip.setLimit(SCAN_LIMIT_NONE);
    chip.setBrightness(BRIGHTNESS_MAX);
    chip.setMatrix(defaultMatrixConfig);
}

void NeuroMonitor::refresh()
{
    memcpy(matrixConfig.data(), defaultMatrixConfig.data(), matrixConfig.size());
}

void NeuroMonitor::recordActivity(int row, int col)
{
    BYTE config = 0b10000000;
    config >>= col;
    matrixConfig.at(row) |= config;
}

void NeuroMonitor::updateMatrix()
{
    chip.setMatrix(matrixConfig);
}

