#include "monitor.h"

using namespace std;

LEDmatrix::LEDmatrix() {}

bool LEDmatrix::init(int pinBase, int spiChan) {
    max7219Setup();
}

void LEDmatrix::registerWrite(unsigned char byte1, unsigned char byte2) {
    digitalWrite();
}


