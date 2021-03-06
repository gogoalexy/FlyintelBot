#ifndef ADXL335_H

#include <cmath>
#include <iostream>
#include "SPIadc.h"

class ADXL335
{
public:
    ADXL335();
    ADXL335(ADC&, int);
    inline int readAcceleration()
    {
        return adc.readChan(chipChan);
    };
    inline int getAction()
    {
        int action = adc.readChan(chipChan)-voltage_0g;
        if(std::abs(action) > threshold)
            return action;
        else
            return 0;
    };
private:
    ADC& adc;
    const int chipChan;
    const int voltage_0g;
    const int threshold;
};

#define ADXL335_H
#endif
