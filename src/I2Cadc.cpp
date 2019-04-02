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

#include "I2Cadc.h"

using namespace std;

i2cADC::i2cADC() : pinBaseDefault(77), i2cChanDefault(0x48), isInit(false)
{}

bool i2cADC::initI2C()
{
    this->pinBase = pinBaseDefault;
    this->i2cChan = i2cChanDefault;
    if(pcf8591Setup(pinBase, i2cChan))
    {
        isInit = true;
        return true;
    }

    return false;
}

bool i2cADC::initI2C(int pinBase, int i2cChan)
{
    this->pinBase = pinBase;
    this->i2cChan = i2cChan;
    if(pcf8591Setup(pinBase, i2cChan))
    {
        isInit = true;
        return true;
    }

    return false;
}
