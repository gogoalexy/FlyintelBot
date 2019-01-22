#include <wiringPi.h>
#include <wiringPiSPI.h>

#include "max7219.h"

/*
unsigned char CATHODE_FUNC(int position)
{
    return 0x01 + position;
}

unsigned char ANODE_FUNC(int position)
{
    return 0x80 >> position;
}

void registerWrite(int fd, unsigned char digit, unsigned char seg)
{
  unsigned char spiData [2];
  spiData [0] = digit;
  spiData [1] = seg;

  wiringPiSPIDataRW (fd, spiData, 2);

}

void matrix_clear(int fd)
{
    for (int i = 0; i < 8; i++)
    {
        registerWrite(fd, CATHODE_FUNC(i), 0x00);
    }
}
*/

/*
 * myRegisterWrite:
 *	Write analog value on the given pin
 *********************************************************************************
 */

static void myRegisterWrite (struct wiringPiNodeStruct *node, int pin, int value)
{
  unsigned char spiData [2] ;
  unsigned char reg1, reg2 ;


  spiData [0] = ((value >> 8) & 0xFF) ;
  spiData [1] = value & 0xFF ;

  wiringPiSPIDataRW (node->fd, spiData, 2) ;
}

/*
 * max7219Setup:
 *	Create a new wiringPi device node for an mcp7219 on the Pi's
 *	SPI interface.
 *********************************************************************************
 */

int max7219Setup (const int pinBase, int spiChannel)
{
  struct wiringPiNodeStruct *node ;

  if (wiringPiSPISetup (spiChannel, 1000000) < 0)
    return FALSE ;

  node = wiringPiNewNode (pinBase, 1) ;

  node->fd          = spiChannel ;
  node->analogWrite = myRegisterWrite ;

  return TRUE ;
}

