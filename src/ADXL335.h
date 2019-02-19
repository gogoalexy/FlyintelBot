#ifndef ADXL335_H

#include "SPIadc.h"

class ADXL335
{
public:
    ADXL335();
    ADXL335(const ADC&, int);
    inline int readAcceleration()
    {
        return adc.readChan(chipChan);
    };
private:
    ADC adc;
    const int chipChan;
    const int voltage_0g;
};

#define ADXL335_H
#endif
