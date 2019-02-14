#include "max7219.h"

using namespace std;

max7219::max7219()
{
    this->fd = -1;
}

int max7219::max7219Setup (int spiChannel)
{
    this->spiChan = spiChannel;
    this->fd = wiringPiSPISetup (spiChan, 1000000);
    if (fd < 0)
    	return -100;

    return fd;
}

int max7219::max7219Setup (int spiChannel, int cascade_num)
{
    this->spiChan = spiChannel;
    this->fd = wiringPiSPISetup (spiChan, 1000000);
    if (fd < 0)
    	return -100;

    this->num_matrix = cascade_num;

    return fd;
}

void max7219::registerWrite (BYTE byte1, BYTE byte2)
{
    unsigned char spiData[2];

    spiData[0] = byte1.to_ulong();
    spiData[1] = byte2.to_ulong();

    wiringPiSPIDataRW (fd, spiData, 2);
}

void max7219::registerWrite (int matrix_n, BYTE byte1, BYTE byte2)//from here
{
    unsigned char spiData[2];

    spiData[0] = byte1.to_ulong();
    spiData[1] = byte2.to_ulong();

    wiringPiSPIDataRW (fd, spiData, 2);
}

void max7219::setROW(int matrix_num, int row, BYTE rowConf)
{
    BYTE reg(row+1);
    registerWrite(reg, rowConf);
}

void max7219::setMatrix(int matrix_num, array<BYTE, 8> allConf)
{
    for(int i = 0; i < allConf.size(); i++)
    {
        setROW(i, allConf[i]);
    }
}

void max7219::setDecode(const BYTE operation)
{
    cout<<DECODE_MODE<<','<<operation<<'\n';
    registerWrite(DECODE_MODE, operation);
}

void max7219::setShutdown(const BYTE operation)
{
    cout<<SHUTDOWN_MODE<<','<<operation<<'\n';
    registerWrite(SHUTDOWN_MODE, operation);
}

void max7219::setLimit(const BYTE num)
{
    registerWrite(0x0B, num);
}

void max7219::setBrightness(const BYTE val)
{
    registerWrite(0x0A, val);
}

void max7219::setTest(const BYTE operation)
{
    cout<<DISPLAY_TEST_MODE<<','<<operation<<'\n';
    registerWrite(DISPLAY_TEST_MODE, operation);
}

max7219::~max7219()
{

}
