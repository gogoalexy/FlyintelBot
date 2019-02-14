#include "max7219.h"

using namespace std;

max7219::max7219()
{
    this->fd = -1;
}

int max7219::max7219Setup (int spiChannel, int spiSpeed = 1000000)
{
    this->spiChan = spiChannel;
    this->spiSpeed = spiSpeed;
    this->fd = wiringPiSPISetup (spiChan, spiSpeed);
    if (fd < 0)
    	return -100;

    return fd;
}

int max7219::max7219Setup (int spiChannel, int spiSpeed = 1000000, int num_of_matrix)
{
    this->spiChan = spiChannel;
    this->fd = wiringPiSPISetup (spiChan, spiSpeed);
    if (fd < 0)
    	return -100;

    this->num_matrix = num_of_matrix;

    return fd;
}

void max7219::registerWrite (BYTE byte1, BYTE byte2)
{
    unsigned char spiData[2];

    spiData[0] = byte1.to_ulong();
    spiData[1] = byte2.to_ulong();

    wiringPiSPIDataRW (fd, spiData, 2);
}

void max7219::registerWrite (int matrix_n, BYTE byte1, BYTE byte2)
{
    int send_bytes = matrix_n * 2;
    unsigned char spiData[send_bytes];

    spiData[0] = byte1.to_ulong();
    spiData[1] = byte2.to_ulong();
    for(int i=2; i<send_bytes; i++)
    {
        spiData[send_bytes] = 0x00;
    }

    wiringPiSPIDataRW (fd, spiData, send_bytes);
}

void max7219::setROW(int row, BYTE rowConf)
{
    BYTE reg(row+1);
    registerWrite(reg, rowConf);
}

void max7219::setROW(int matrix_num, int row, BYTE rowConf)
{
    BYTE reg(row+1);
    registerWrite(matrix_num, reg, rowConf);
}

void max7219::setMatrix(array<BYTE, 8> allConf)
{
    for(int i = 0; i < allConf.size(); i++)
    {
        setROW(i, allConf[i]);
    }
}

void max7219::setMatrix(int matrix_num, array<BYTE, 8> allConf)
{
    for(int i = 0; i < allConf.size(); i++)
    {
        setROW(matrix_num, i, allConf[i]);
    }
}

void max7219::setDecode(const BYTE operation)
{
    for()
    {
        registerWrite(DECODE_MODE, operation);
    }
}

void max7219::setShutdown(const BYTE operation)
{
    for(int n=0; n<num_matrix; n++)
    {
        registerWrite(n, SHUTDOWN_MODE, operation);
    }
}

void max7219::setLimit(const BYTE limit)
{
    for(int n=0; n<num_matrix; n++)
    {
        registerWrite(n, 0x0B, limit);
    }
}

void max7219::setBrightness(const BYTE val)
{
    for(int n; n<matrix_n; n++)
    {
        registerWrite(n, 0x0A, val);
    }
}

void max7219::setTest(const BYTE operation)
{
    for()
    {
        registerWrite(DISPLAY_TEST_MODE, operation);
    }
}

max7219::~max7219()
{

}
