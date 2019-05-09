#include "ADXL335.h"

using namespace std;

//ADXL335::ADXL335() : chipChan(7), voltage_0g(330), threshold(20)
//{
//    cout<<"ADC is undefined."<<endl;
//}

ADXL335::ADXL335(ADC& mcp3008, int sensorID) : adc(mcp3008), chipChan(sensorID), voltage_0g(330), threshold(20)
{}
