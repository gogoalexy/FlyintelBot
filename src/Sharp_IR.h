/*
 *	  This file is part of FlyintelBot.
 *    Copyright (C) 2018  Alex Huang-Yu Yao
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
