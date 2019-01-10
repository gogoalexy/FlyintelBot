#include "monitor.h"

using namespace std;

LEDmatrix::LEDmatrix() {}

bool LEDmatrix::init(int pinBase, int spiChan) {
    max7219Setup();
}

void LEDmatrix::LEDwrite(unsigned short row, unsigned short column, bool state) {

}


