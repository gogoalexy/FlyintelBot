#include <iostream>
#include <wiringPi.h>
#include "../src/HC_SR04.h"

using namespace std;

int main() {
	if(wiringPiSetup() == -1){
		return -1;
	}
	pinMode(15, OUTPUT);
	HCSR04 sound(15, 16, 10000);

	while(true){
		cout<<sound.UsoundRange()<<endl;
	}
	return 0;
}
