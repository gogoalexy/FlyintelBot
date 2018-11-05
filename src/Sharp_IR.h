#ifndef SHARP_IR_H

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <mcp3004.h>
#include <iostream>
#include "sensor.h"

class SharpIR : public Sensor {
public:
	SharpIR(short, int);
	void init() override;
	unsigned int range() override;
	int IRrange();
private:
	short spi_chan;
	const int BASE = 100;
	int ic_chan;
};

#define SHARP_IR_H
#endif
