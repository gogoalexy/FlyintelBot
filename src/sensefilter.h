#ifndef SENSE_FILTER_H

#include <cmath>

class LinearFilter{
public:

    LinearFilter(float, float, float);
    float slope();
    float FilterGen(int);

private:
    float mean;
    float max;
    float edgelen;
};

#define SENSE_FILTER_H
#endif
