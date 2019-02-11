#include "monitor.h"

using namespace std;

NeuroMonitor::NeuroMonitor()
{

}

int NeuroMonitor::init(int pibBase, int spiChan)
{
    if(!max7219Setup(pinBase, spiChan))
    {
        return -1;
    }
    memcpy(matrixConfig, defaultMatrixConfig, size.matrixConfig);
    return 0;
}

void NeuroMonitor::refresh()
{
    memcpy(matrixConfig, defaultMatrixConfig, size.matrixConfig);
}

void NeuroMonitor::recordActivity(int row, int col, bool state)
{
    unsigned char config = 0b00000000;
    if(state)
    {
        config = 0x80 >> col;
    }
    matrixConfig.at(row) |= config;
}

void NeuroMonitor::update1Matrix(int pin)
{
    for(unsigned char addr = 0x01, addr <= 0x08, addr++)
    {
        unsigned short val = bytes2short(addr, matrixConfig.at((short)addr));
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
