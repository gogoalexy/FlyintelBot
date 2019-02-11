#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "max7219.h"

/*
 * myRegisterWrite:
 *  Write byte value on the given pin
 *********************************************************************************
 */

static void myRegisterWrite (struct wiringPiNodeStruct *node, int pin, unsigned short value)
{
    unsigned char spiData [2] ;
    unsigned char reg1, reg2 ;

    //bitmask 0xFF = b0000000011111111
    spiData [0] = ((value >> 8) & 0xFF) ;
    spiData [1] = value & 0xFF ;

    wiringPiSPIDataRW (node->fd, spiData, 2) ;
}

/*
 * max7219Setup:
 *  Create a new wiringPi device node for an max7219 on the Pi's
 *  SPI interface.
 *********************************************************************************
 */

int max7219Setup (const int pinBase, int spiChannel)
{
    struct wiringPiNodeStruct *node ;

    if (wiringPiSPISetup (spiChannel, 1000000) < 0)
        return -100 ;

    node = wiringPiNewNode (pinBase, 1) ;

    node->fd          = spiChannel ;
    node->analogWrite = myRegisterWrite ;

    return 0 ;
}

