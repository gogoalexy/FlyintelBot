#ifndef MAX7219_H

#ifdef __cplusplus
extern "C" {
#endif

extern int max7219Setup (int pinBase, int spiChannel) ;

#ifdef __cplusplus
}
#endif

const unsigned char DECODE_MODE = 0x09;
const unsigned char INTENSITY = 0x0A;
const unsigned char SCAN_LIMIT = 0x0B;
const unsigned char SHUTDOWN = 0x0C;
const unsigned char DISPLAY_TEST = 0x0F;
const unsigned char ENTER_SHUTDOWN = 0x00;
const unsigned char EXIT_SHUTDOWN = 0x01;
//const unsigned char DIGIT_REG{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

#define MAX7219_H
#endif
