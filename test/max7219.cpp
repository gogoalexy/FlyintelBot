#include "max7219.h"

using namespace std;

max7219::max7219()
{
    this->fd = -1;
    this->num_of_matrix = 1;
}

int max7219::max7219Setup(int spiChannel, int spiSpeed)
{
    this->spiChan = spiChannel;
    this->fd = wiringPiSPISetup(spiChan, spiSpeed);

    return fd;
}

void max7219::registerWrite(const BYTE byte1, const BYTE byte2)
{
    unsigned char spiData[2];

    spiData[0] = (unsigned char) byte1.to_ulong();
    spiData[1] = (unsigned char) byte2.to_ulong();

    wiringPiSPIDataRW(fd, spiData, 2);
}


void max7219::setShutdown(const BYTE command)
{
    registerWrite(SHUTDOWN_MODE, command);
}

void max7219::setDecode(const BYTE command)
{
    registerWrite(BCD_DECODE_MODE, command);
}

void max7219::setLimit(const BYTE limit)
{
    registerWrite(SCAN_LIMIT, limit);
}

void max7219::setBrightness(const BYTE intensity)
{
    registerWrite(BRIGHTNESS, intensity);
}

void max7219::setTest(const BYTE command)
{
    registerWrite(DISPLAY_TEST_MODE, command);
}

/*row counts from zero*/
void max7219::setROW(int row, const BYTE rowConf)
{
    BYTE reg(row+1);
    #ifdef DEBUG
        cout<<reg<<','<<rowConf<<'\n';
    #endif
    registerWrite(reg, rowConf);
}

void max7219::setMatrix(const array<BYTE, 8> allConf)
{
    for(int i=0; i<allConf.size(); i++)
    {
        setROW(i, allConf.at(i));
    }
}

max7219::~max7219()
{

}
