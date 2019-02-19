/*
 *	  This file is part of FlyintelBot.
 *    Copyright (C) 2019  Alex Huang-Yu Yao
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
#include <SPIadc.h>
#include <iostream>
#include "sensor.h"

class SharpIR : public Sensor
{
public:
    SharpIR();
    SharpIR(const ADC&, int);
    unsigned int range() override;
    inline int IRrange()
    {
	    return adc.readChan(chipChan);
    };

private:
    ADC adc;
    const int chipChan;
};

#define SHARP_IR_H
#endif
