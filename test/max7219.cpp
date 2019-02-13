#include "max7219.h"

using namespace std;

max7219::max7219()
{
    
}

int max7219::max7219Setup (int spiChannel)
{
    this->spiChan = spiChannel;
    this->fd = wiringPiSPISetup (spiChan, 1000000);
    if (fd < 0)
    	return -100;

    return fd;
}

void max7219::registerWrite (BYTE byte1, BYTE byte2)
{
    unsigned char spiData [2] ;

    spiData [0] = byte1;
    spiData [1] = byte2;

    wiringPiSPIDataRW (fd, spiData, 2) ;
}

void max7219::setROW(int row, BYTE rowConf)
{
    registerWrite();
}

void max7219::setDecode(const BYTE operation)
{

}

void max7219::setShutdown(const BYTE operation)
{
    registerWrite(pin, val);
}

void max7219::setTest(const BYTE operation)
{
    registerWrite(pin, val);
}

max7219::~max7219()
{
    
}
