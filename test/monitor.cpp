#include "monitor.h"

using namespace std;

NeuroMonitor::NeuroMonitor()
{

}

int NeuroMonitor::init(int spiChan)
{
    if(!max7219Setup(spiChan))
    {
        return -1;
    }
    memcpy(matrixConfig.data(), defaultMatrixConfig.data(), matrixConfig.size());
    return 0;
}

void NeuroMonitor::refresh()
{
    memcpy(matrixConfig.data(), defaultMatrixConfig.data(), matrixConfig.size());
}

void NeuroMonitor::recordActivity(int row, int col, bool state)
{
    unsigned char config = 0b10000000;
    if(state)
    {
        config >>= col;
        matrixConfig.at(row) |= config;
    }
}

void NeuroMonitor::update1Matrix(int pin)
{
    for(unsigned char addr = 0x01; addr <= 0x08; addr+=0x01)
    {
        unsigned short val = bytes2short(addr, matrixConfig.at((short)addr-1));
        analogWrite(pin, val);
    }
}


