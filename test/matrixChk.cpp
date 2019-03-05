#include <wiringPi.h>
#include <array>
#include "max7219.h"

using namespace std;

int main() {

    BYTE row1 (2);
    BYTE row2 (4);
    BYTE val1 (0b11110011);
    BYTE val2 (0b11001111);
    max7219 led;

	if (led.max7219Setup(1, 1000000) < 0) {

		exit(1);
	}
	led.setShutdown(EXIT_SHUTDOWN);
	led.setTest(EXIT_DISPLAY_TEST);
	led.setDecode(BCD_DECODE_NONE);
	led.setLimit(SCAN_LIMIT_NONE);
	led.setBrightness(BRIGHTNESS_HALF);
	//for (;;){
		led.setROW(0, 0b00000000);
		led.setROW(1, 0b00000000);
		led.setROW(2, 0b00000000);
		led.setROW(3, 0b00000000);
		led.setROW(4, val1);
		led.setROW(5, 0b00000000);
		led.setROW(6, 0b00000000);
		led.setROW(7, 0b00000000);
    		delay(300);
	//}
return 0;
}
