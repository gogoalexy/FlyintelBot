#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "max7219.h"

/*
 * mydigitalWrite:
 *	Write value on the given pin
 *********************************************************************************


static void mydigitalWrite (struct wiringPiNodeStruct *node, unsigned char addr, unsigned char value)
{
  unsigned char spiData [2] ;
  int chan = pin - node->pinBase ;

  spiData [0] = addr;
  spiData [1] = value;

  wiringPiSPIDataRW (node->fd, spiData, 2);
}
*/

/*
 * max7219Setup:
 *	Create a new wiringPi device node for an max7219 on the Pi's
 *	SPI interface.
 *********************************************************************************


int max7219Setup (const int pinBase, int spiChannel)
{
  struct wiringPiNodeStruct *node ;

  if (wiringPiSPISetup (spiChannel, 1000000) < 0)
    return FALSE;

  node = wiringPiNewNode (pinBase, 2);

  node->fd          = spiChannel;
  node->digitalWrite = mydigitalWrite;

  return TRUE;
}
*/

max7219::max7219() {}

bool max7219::init(int spiChannel)
{
  this->fd = wiringPiSPISetup (spiChannel, 1000000);
  if ( fd < 0)
    return FALSE;

  return TRUE;
}

void max7219::registerWrite(unsigned char, unsigned char)
{
  unsigned char spiData [2];
  spiData [0] = addr;
  spiData [1] = value;

  wiringPiSPIDataRW (fd, spiData, 2);

}

inline unsigned char max7219::ANODE_FUNC(int position)
{
    return 0x80 >> position;
}

