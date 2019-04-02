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
#ifndef SPI_ADC_H

#include <wiringPi.h>
#include <mcp3004.h>
#include "adc.h"

class spiADC : public ADC
{
public:
    spiADC();
    bool initSPI();
    bool initSPI(int, int);
    inline bool isInit() override
    {
        return init;
    }
    inline int whichPin() override
    {
        return pinBase;
    }
    inline int readChan(int chipChan) override
    {
        return analogRead(pinBase + chipChan);
    }

protected:
    const int pinBaseDefault;
    const int spiChanDefault;
    const int spiSpeedDefault;
    int pinBase;
    int spiChan;
};

#define SPI_ADC_H
#endif
