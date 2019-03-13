#include <iostream>
#include <wiringPi.h>
#include "../src/HC_SR04.h"

using namespace std;

int main() {
	if(wiringPiSetupGpio() == -1){
		return -1;
	}

	HCSR04 sound(21, 26, 10000);
	sound.init();

	while(true){
		cout<<sound.UsoundRange()<<endl;
	}
	return 0;
}
