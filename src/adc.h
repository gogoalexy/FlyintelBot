#ifndef ADC_H

#include <mcp3004.h>

class ADC
{
public:
    ADC();
    int initSPI();
protected:
    int spiChan;
    int pinBase;
}
//both included by ir adxl
//foward declaration
#define ADC_H
#endif
