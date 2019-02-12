#include "max7219.h"

/*
 * myRegisterWrite:
 *  Write byte value on the given pin
 *********************************************************************************
 */

void registerWrite (int fd, BYTE byte1, BYTE byte2)
{
    unsigned char spiData [2] ;

    spiData [0] = byte1;
    spiData [1] = byte2;

    wiringPiSPIDataRW (fd, spiData, 2) ;
}

/*
 * max7219Setup:
 *  Create a new wiringPi device node for an max7219 on the Pi's
 *  SPI interface.
 *********************************************************************************
 */

int max7219Setup (int spiChannel)
{
    int fd = wiringPiSPISetup (spiChannel, 1000000);
    if (fd < 0)
    	return -100;

    return fd;
}

