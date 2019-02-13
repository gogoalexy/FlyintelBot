#ifndef MAX7219_H

#include <iostream>
#include <bitset>
#include <wiringPiSPI.h>

typedef std::bitset<8> BYTE;

const BYTE INTENSITY (0x0A);

const BYTE SCAN_LIMIT (0x0B);

const BYTE DECODE_MODE (0x09);
const BYTE DECODE_ALL (0xFF);
const BYTE DECODE_NONE (0x00);

const BYTE SHUTDOWN_MODE (0x0C);
const BYTE ENTER_SHUTDOWN (0x00);
const BYTE EXIT_SHUTDOWN (0x01);

const BYTE DISPLAY_TEST_MODE (0x0F);
const BYTE ENTER_DISPLAY_TEST (0x01);
const BYTE EXIT_DISPLAY_TEST (0x00);

class max7219
{
public:
    max7219();
    int max7219Setup (int spiChannel);
    void setROW(int, BYTE);
    void setDecode(BYTE);
    void setShutdown(BYTE);
    void setLimit(BYTE);
    void setBrightness(BYTE);
    void setTest(BYTE);
    ~max7219();
protected:
    void registerWrite(BYTE, BYTE);
private:
    int spiChan;
    int fd;
};

#define MAX7219_H
#endif
