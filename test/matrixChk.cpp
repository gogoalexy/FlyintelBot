#include <wiringPi.h>
#include <array>
#include "max7219.h"

using namespace std;

int main() {

    array<BYTE, 8> data
{
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000,
0b00000000
};
BYTE value (0b11110011);
    max7219 led;

	if (led.max7219Setup(1, 1000000) < 0) {

		exit(1);
	}
    led.setShutdown(EXIT_SHUTDOWN);
    led.setTest(EXIT_DISPLAY_TEST);
    led.setDecode(BCD_DECODE_NONE);
    led.setLimit(SCAN_LIMIT_NONE);
    led.setBrightness(BRIGHTNESS_MAX);
	for (;;){
//	 led.setTest(ENTER_DISPLAY_TEST);
  led.setMatrix(data);
       	led.setROW(1, 6, value);
delay(300);
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
