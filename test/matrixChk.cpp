#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <wiringPi.h>
#include "max7219.h"

int main(int argc, char** argv) {
	//uint8_t on[] = { 0x0C, 0x01 };
	//uint8_t off[] = { 0xFF, 0x01 };
//	uint8_t buf[2] = {0xFF, 0x00};
    BYTE row (0x02);

    max7219 led;

	if (led.max7219Setup(1) < 0) {
		printf ("SPI Setup failed\n");
		exit(1);
	}
    led.setShutdown(EXIT_SHUTDOWN);
    led.setTest(EXIT_DISPLAY_TEST);
    led.setDecode(DECODE_NONE);

	for (;;) {
		int val = 0x00 | 0xFF<<8;
       led.setROW(1, row);
		//delay(5000);
	//	val = off[0] | off[1]<<8;
	//	analogWrite(110, val);
		//sleep(1);
	}
return 0;
}

/*
using namespace std;

int main()
{
    NeuroMonitor led;
    led.init(128, 1);
    led.setShutdown(128, EXIT_SHUTDOWN);
    led.setTest(128, EXIT_DISPLAY_TEST);
    led.setDecode(128, DECODE_NONE);

    while(true)
    {
        led.refresh();
	unsigned char x, y;
        cout<<"N1"<<'\n';
        //cin>>x>>y;
x=0;
y=5;
        led.recordActivity(x, y, true);
        cout<<"N2"<<'\n';
        //cin>>x>>y;
x=2;
y=1;
        led.recordActivity(x, y, true);
        cout<<"N3"<<'\n';
        //cin>>x>>y;
x=7;
y=7;
        led.recordActivity(x, y, true);

        //led.refresh();
        led.update1Matrix(128);
    }

    return 0;
}
*/
