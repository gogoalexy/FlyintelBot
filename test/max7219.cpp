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

bool max7219_init(int spiChannel)
{
  max7219fd = wiringPiSPISetup (spiChannel, 1000000);
  if ( max7219fd < 0)
    return FALSE;

  return TRUE;
}

void registerWrite(unsigned char, unsigned char)
{
  unsigned char spiData [2];
  spiData [0] = addr;
  spiData [1] = value;

  wiringPiSPIDataRW (max7219fd, spiData, 2);

}

inline unsigned char CATHODE_FUNC(int position)
{
    return 0x01 + position;
}

inline unsigned char ANODE_FUNC(int position)
{
    return 0x80 >> position;
}

void matrix_clear()
{
    for (int i = 0; i < 8; i++)
    {
        registerWrite(CATHODE_FUNC(i), 0x00);
    }
}

