#include "monitor.h"

using namespace std;

NeuroMonitor::NeuroMonitor()
{

}

int NeuroMonitor::init(int pinBase, int spiChan)
{
    if(!max7219Setup(pinBase, spiChan))
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

void NeuroMonitor::setDecode(int pin, const unsigned char operation)
{
    unsigned short val = bytes2short(DECODE_MODE, operation);
    analogWrite(pin, val);
}

void NeuroMonitor::setShutdown(int pin, const unsigned char operation)
{
    unsigned short val = bytes2short(SHUTDOWN_MODE, operation);
    analogWrite(pin, val);
}

void NeuroMonitor::setTest(int pin, const unsigned char operation)
{
    unsigned short val = bytes2short(DISPLAY_TEST_MODE, operation);
    analogWrite(pin, val);
}
