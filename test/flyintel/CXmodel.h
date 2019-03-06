#ifndef CX_MODEL_H

#include "connect_to_flysim.h"
#include "flyintel.h"
#include <array>
#include <queue>
#include <iostream>

class CentralComplexStimulator
{
public:
    CentralComplexStimulator();
    void keepState();
    void switchState();
    void shiftRight();
    void shiftLeft();

private:
    const float PB_HALF_FR;
    const float RING_PEI_FR;
    const float RING_PEN_FR;

};

class CentralComplexDecoder : public Flyintel
{
public:
    CentralComplexDecoder();
    std::array<int, 16> sortingHat(char*);
    std::queue<int> findBump();
    void clean();

private:
    const int EIP2EB[16][4];
    const int SIZE_POPULATION;
    std::array<int, 16> activityEB;

};


#define CX_MODEL_H
#endif