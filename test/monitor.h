#ifndef MONITOR_H

#include <vector>
#include <array>
#include <cstring>
#include <wiringPi.h>
#include "net_struct_def.h"
#include "max7219.h"

const unsigned char INTENSITY = 0x0A;

const unsigned char SCAN_LIMIT = 0x0B;

const unsigned char DECODE_MODE = 0x09;
const unsigned char DECODE_ALL = 0xFF;
const unsigned char DECODE_NONE = 0x00;

const unsigned char SHUTDOWN_MODE = 0x0C;
const unsigned char ENTER_SHUTDOWN = 0x00;
const unsigned char EXIT_SHUTDOWN = 0x01;

const unsigned char DISPLAY_TEST_MODE = 0x0F;
const unsigned char ENTER_DISPLAY_TEST = 0x01;
const unsigned char EXIT_DISPLAY_TEST = 0x00;

class NeuroMonitor
{
public:
    NeuroMonitor();
    int init(int, int);
    void refresh();

    void recordActivity(int, int, bool);
    void update1Matrix(int);
    void setDecode(int, unsigned char);
    void setShutdown(int, unsigned char);
    void setTest(int, unsigned char);

private:
    std::array<unsigned char, 8> matrixConfig;

    inline unsigned short bytes2short(unsigned char byte1, unsigned char byte2)
    {
        return byte2 | (byte1 << 8);
    }
};

#define MONITOR_H
#endif
