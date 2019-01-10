#ifndef MAX7219_H

#ifdef __cplusplus
extern "C" {
#endif

extern int max7219Setup (int pinBase, int spiChannel) ;

#ifdef __cplusplus
}
#endif

const unsigned char DIGIT_REG{0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};

#define MAX7219_H
#endif
