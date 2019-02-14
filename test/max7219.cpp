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

int max7219::max7219Setup(int spiChannel, int spiSpeed, int num_of_matrix)
{
    this->spiChan = spiChannel;
    this->fd = wiringPiSPISetup(spiChan, spiSpeed);

    this->num_of_matrix = num_of_matrix;

    return fd;
}

void max7219::registerWrite(const BYTE byte1, const BYTE byte2)
{
    unsigned char spiData[2];

    spiData[0] = (unsigned char) byte1.to_ulong();
    spiData[1] = (unsigned char) byte2.to_ulong();

    wiringPiSPIDataRW(fd, spiData, 2);
}

void max7219::registerWrite(int matrix_n, const BYTE byte1, const BYTE byte2)
{
    int bytes2send = num_of_matrix * 2;
    unsigned char spiData[bytes2send];

    for(int i=0; i<bytes2send; i++)
    {
        spiData[i] = (unsigned char) NO_OP.to_ulong();
    }
    spiData[(num_of_matrix-matrix_n)*2] = (unsigned char) byte1.to_ulong();
    spiData[(num_of_matrix-matrix_n)*2+1] = (unsigned char) byte2.to_ulong();

    wiringPiSPIDataRW(fd, spiData, bytes2send);
}

void max7219::setShutdown(const BYTE command)
{
    for(int n=1; n<=num_of_matrix; n++)
    {
        registerWrite(n, SHUTDOWN_MODE, command);
    }
}

void max7219::setDecode(const BYTE command)
{
    for(int n=1; n<=num_of_matrix; n++)
    {
        registerWrite(n, BCD_DECODE_MODE, command);
    }
}

void max7219::setLimit(const BYTE limit)
{
    for(int n=1; n<=num_of_matrix; n++)
    {
        registerWrite(n, SCAN_LIMIT, limit);
    }
}

void max7219::setBrightness(const BYTE intensity)
{
    for(int n=1; n<=num_of_matrix; n++)
    {
        registerWrite(n, BRIGHTNESS, intensity);
    }
}

void max7219::setTest(const BYTE command)
{
    for(int n=0; n<num_of_matrix; n++)
    {
        registerWrite(DISPLAY_TEST_MODE, command);
    }
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

void max7219::setROW(int matrix_n, int row, const BYTE rowConf)
{
    BYTE reg(row+1);
    registerWrite(matrix_n, reg, rowConf);
}

void max7219::setMatrix(const array<BYTE, 8> allConf)
{
    for(int i=0; i<allConf.size(); i++)
    {
        setROW(i, allConf.at(i));
    }
}

void max7219::setMatrix(int matrix_num, const array<BYTE, 8> allConf)
{
    for(int i=0; i<allConf.size(); i++)
    {
        setROW(matrix_num, i, allConf.at(i));
    }
}

max7219::~max7219()
{

}
