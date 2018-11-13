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

#include "Sharp_IR.h"

using namespace std;

SharpIR::SharpIR(short spi_chan, int ic_chan){
    this->spi_chan = spi_chan;
    this->ic_chan = ic_chan;
    //fixed spi speed
    //spisetup check
    if(!chkSPI){
    	//if(wiringPiSPISetup() == -1){
	//	cout<<"SPI setup failed."<<endl;
	//	return;
	//}
	chkSPI = true;
    
        mcp3004Setup(BASE, this->spi_chan);
    }
}

void SharpIR::init() {
    if(wiringPiSPISetup(this->spi_chan, 500000) == -1){
		    cout<<"SPI setup failed."<<endl;
		    return;
		}
		mcp3004Setup(BASE, this->spi_chan);
}

unsigned int SharpIR::range() {
    return analogRead(BASE + ic_chan);
}

int SharpIR::IRrange(){
	return analogRead(BASE + ic_chan);
}
