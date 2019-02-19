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

#include <mcp3004.h>

class ADC
{
public:
    ADC();
    bool initSPI();
    bool initSPI(int, int);
    inline bool isInit()
    {
        return isInit;
    };
    inline int whichPin()
    {
        return pinBase;
    };
    inline int readChan(int chipChan)
    {
        return analogRead(pinBase + chipChan);
    };

protected:
    const int pinBaseDefault;
    const int spiChanDefault;
    const int spiSpeedDefault;
    int pinBase;
    int spiChan;
    bool isInit;
};

#define SPI_ADC_H
#endif
