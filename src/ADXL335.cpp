#include "ADXL335.h"

using namespace std;

ADXL335::ADXL335()
{
    cout<<"ADC is undefined."<<endl;
}

ADXL335::ADXL335(const ADC& mcp3008, int sensorID) : adc(mcp3008), chipChan(sensorID), voltage_0g(330)
{ }

