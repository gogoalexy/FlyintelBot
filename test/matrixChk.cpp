#include <wiringPi.h>
#include "max7219.h"

using namespace std;

int main() {

    BYTE data (0b01001100);

    max7219 led;

	if (led.max7219Setup(1, 1000000, 2) < 0) {
		cout<<"SPI Setup failed"<<"\n";
		exit(1);
	}
    led.setShutdown(EXIT_SHUTDOWN);
    led.setTest(EXIT_DISPLAY_TEST);
    led.setDecode(DECODE_NONE);
    led.setLimit(SCAN_LIMIT_NONE);
    led.setBrightness(BRIGHTNESS_MAX);
	for (;;) {
//led.setTest(ENTER_DISPLAY_TEST);
       led.setROW(1, 2, data);
       led.setROW(2, 4, data);
	   delay(500);
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
