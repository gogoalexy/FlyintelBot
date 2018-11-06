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
