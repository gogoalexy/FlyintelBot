#ifndef ADXL335_H

class ADXL335
{
public:
    int readAcceleration();
private:
    short spi_chan;
    const int BASE = 100;
    int ic_chan;
    const voltage_0g;
}

#define ADXL335_H
#endif
