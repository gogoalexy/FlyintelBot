#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "max7219.h"

/*
 * myAnalogWrite:
 *	Write analog value on the given pin
 *********************************************************************************
 */

static void myAnalogWrite (struct wiringPiNodeStruct *node, int pin, int value)
{
  unsigned char spiData [2] ;
  unsigned char chanBits, dataBits ;
  int chan = pin - node->pinBase ;

  if (chan == 0)
    chanBits = 0x30 ;
  else
    chanBits = 0xB0 ;

  chanBits |= ((value >> 4) & 0x0F) ;
  dataBits  = ((value << 4) & 0xF0) ;

  spiData [0] = chanBits ;
  spiData [1] = dataBits ;

  wiringPiSPIDataRW (node->fd, spiData, 2) ;
}

/*
 * mcp4802Setup:
 *	Create a new wiringPi device node for an mcp4802 on the Pi's
 *	SPI interface.
 *********************************************************************************
 */

int mcp4802Setup (const int pinBase, int spiChannel)
{
  struct wiringPiNodeStruct *node ;

  if (wiringPiSPISetup (spiChannel, 1000000) < 0)
    return FALSE ;

  node = wiringPiNewNode (pinBase, 2) ;

  node->fd          = spiChannel ;
  node->analogWrite = myAnalogWrite ;

  return TRUE ;
}
