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

#include "SPIadc.h"

using namespace std;

spiADC::spiADC() : pinBaseDefault(88), spiChanDefault(0), spiSpeedDefault(1000000), isInit(false)
{
    /*SPI speed is defined in mcp3004Setup().*/

}

bool spiADC::initSPI()
{
    this->pinBase = pinBaseDefault;
    this->spiChan = spiChanDefault;
    if(mcp3004Setup(pinBase, spiChan))
    {
        isInit = true;
        return true;
    }

    return false;
}

bool spiADC::initSPI(int pinBase, int spiChan)
{
    this->pinBase = pinBase;
    this->spiChan = spiChan;
    if(mcp3004Setup(pinBase, spiChan))
    {
        isInit = true;
        return true;
    }

    return false;
}
