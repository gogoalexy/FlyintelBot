#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "max7219.h"

/*
 * mydigitalWrite:
 *	Write analog value on the given pin
 *********************************************************************************
 */

static void mydigitalWrite (struct wiringPiNodeStruct *node, int addr, int value)
{
  unsigned char spiData [2] ;
  unsigned char digitreg, dataBits;
  int chan = pin - node->pinBase ;

  digitreg = DIGIT_REG[addr];
  if (value == 1){
    dataBits = 0xFF;
  }else if (value == 0){
    dataBits = 0x00;
  }

  spiData [0] = digitreg;
  spiData [1] = dataBits;

  wiringPiSPIDataRW (node->fd, spiData, 2);
}

/*
 * max7219Setup:
 *	Create a new wiringPi device node for an max7219 on the Pi's
 *	SPI interface.
 *********************************************************************************
 */

int max7219Setup (const int pinBase, int spiChannel)
{
  struct wiringPiNodeStruct *node ;

  if (wiringPiSPISetup (spiChannel, 1000000) < 0)
    return FALSE ;

  node = wiringPiNewNode (pinBase, 8) ;

  node->fd          = spiChannel ;
  node->digitalWrite = mydigitalWrite ;

  return TRUE ;
}
