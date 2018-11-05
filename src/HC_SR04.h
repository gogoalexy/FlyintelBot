#ifndef HC_SR04_H

#include <wiringPi.h>
#include "sensor.h"

class HCSR04 : public Sensor {
public:
	HCSR04(short, short, int);
	void init() override;
	unsigned int range() override;
	unsigned long UsoundRange();
private:
	short TrigPin;
	short EchoPin;
	int timeout;
	unsigned long travelTime;
};

#define HC_SR04_H
#endif
