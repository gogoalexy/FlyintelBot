#ifndef MAX7219_H

#ifdef DEBUG
    #include <iostream>
#endif

#include <bitset>
#include <array>
#include <wiringPiSPI.h>

typedef std::bitset<8> BYTE;

const BYTE NO_OP (0x00);

const BYTE BCD_DECODE_MODE (0x09);
const BYTE BCD_DECODE_ALL (0xFF);
const BYTE BCD_DECODE_NONE (0x00);

const BYTE SCAN_LIMIT (0x0B);
const BYTE SCAN_LIMIT_NONE (0x07);

const BYTE BRIGHTNESS (0x0A);
const BYTE BRIGHTNESS_MIN (0x00);
const BYTE BRIGHTNESS_HALF (0x08);
const BYTE BRIGHTNESS_MAX (0x0F);

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
    int max7219Setup(int, int);
    int max7219Setup(int, int, int);
    void setShutdown(BYTE);
    void setDecode(BYTE);
    void setLimit(BYTE);
    void setBrightness(BYTE);
    void setTest(BYTE);
    void setROW(int, BYTE);
    void setROW(int, int, BYTE);
    void setMatrix(std::array<BYTE, 8>);
    void setMatrix(int, std::array<BYTE, 8>);
    ~max7219();
protected:
    void registerWrite(BYTE, BYTE);
    void registerWrite(int, BYTE, BYTE);
    void registerWrite(BYTE, BYTE, BYTE, BYTE);//bicolor
private:
    int spiChan;
    int fd;
    int num_of_matrix;
};

#define MAX7219_H
#endif
