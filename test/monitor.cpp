#include "monitor.h"

using namespace std;

NeuroMonitor::NeuroMonitor(int spiChannel = 1)
{
    memcpy(matrixConfig.data(), defaultMatrixConfig.data(), matrixConfig.size());

    this->spiChan = spiChannel;
    if(!isSPIinit())
    {
        if(!max7219Setup(spiChan))
        {
            exit(1);
        }
    }
}

bool NeuroMonitor::isSPIinit()
{
    if(fd <= 0)
    {
        return false;
    }
    return true;
}

void NeuroMonitor::init()
{        
    setShutdown(EXIT_SHUTDOWN);
    setLimit(SCAN_LIMIT_NONE);
    setBrightness(BRIGHTNESS_MAX);
    setAllMatrix(defaultMatrixConfig);
    
    return fd;
}


void NeuroMonitor::refresh()
{
    memcpy(matrixConfig.data(), defaultMatrixConfig.data(), matrixConfig.size());
}

void NeuroMonitor::recordActivity(int row, int col, bool state)
{
    BYTE config = 0b10000000;
    if(state)
    {
        config >>= col;
        matrixConfig.at(row) |= config;
    }
}

void NeuroMonitor::updateMatrix()
{
    for(unsigned char addr = 0x01; addr <= 0x08; addr+=0x01)
    {

    }
}


