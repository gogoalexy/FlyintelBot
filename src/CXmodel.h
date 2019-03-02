#ifndef CX_MODEL_H

#include "connect_to_flysim.h"

class CentralComplex
{
public:
    CentralComplex();
    void keepState();
    void switchState();
    void shiftRight();
    void shiftLeft();

private:
    const float PB_HALF_FR;
    const float RING_PEI_FR;
    const float RING_PEN_FR;

};

#define CX_MODEL_H
#endif