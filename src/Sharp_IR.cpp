#include "Sharp_IR.h"

SharpIR::SharpIR(short spi_chan = 0, int ic_chan = 0){
    this->spi_chan = spi_chan;
    this->ic_chan = ic_chan;
    //fixed spi speed
    //spisetup check
    if(wiringPiSPISetup(this->spi_chan, 500000) == -1){
		cout<<"SPI setup failed."<<endl;
		return;
	}
    mcp3004Setup(BASE, this->spi_chan);
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
