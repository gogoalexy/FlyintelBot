#ifndef SCX_MODEL_H

#include "connect_to_flysim.h"
#include "flyintel.h"
#include <array>
#include <string>
#include <iostream>

class SimpleCXStimulator
{
public:
    void stiLoc(int, int);
    void shiftRight(int);
    void shiftLeft(int);

};

class SimpleCXDecoder : public Flyintel
{
public:
    std::array<int, 16> sortingHat(char*);
    void clean();

};


#define SCX_MODEL_H
#endif
