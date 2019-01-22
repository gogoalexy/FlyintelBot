#ifndef MAX7219_H

#ifdef __cplusplus
extern "C" {
#endif

extern int max7219Setup (int pinBase, int spiChannel) ;

#ifdef __cplusplus
}
#endif

/*
int max7219_init(int);
unsigned char CATHODE_FUNC(int);
unsigned char ANODE_FUNC(int);
void registerWrite(int, unsigned char, unsigned char);
void matrix_clear(int);
//void setBrightness();
//void setMode();

//extern int  max7219fd;

const unsigned char DECODE_MODE = 0x09;
const unsigned char INTENSITY = 0x0A;
const unsigned char SCAN_LIMIT = 0x0B;
const unsigned char SHUTDOWN = 0x0C;
const unsigned char DISPLAY_TEST = 0x0F;

const unsigned char ENTER_DECODE = 0xFF;
const unsigned char EXIT_DECODE = 0x00;
const unsigned char ENTER_SHUTDOWN = 0x00;
const unsigned char EXIT_SHUTDOWN = 0x01;
*/
#define MAX7219_H
#endif
