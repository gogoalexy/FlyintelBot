#ifndef HC_SR04_H

#include <wiringPi.h>

class HCSR04{
public:
	HCSR04(short, short, int);
	unsigned long UsoundRange();
private:
	short TrigPin;
	short EchoPin;
	int timeout;
	unsigned long travelTime;
};

#define HC_SR04_H
#endif
