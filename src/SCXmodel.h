#ifndef SCX_MODEL_H

#include "connect_to_flysim.h"
#include "flyintel.h"
#include <array>
#include <queue>
#include <string>
#include <iostream>
#include <tuple>
#include "max7219.h"

class SimpleCXStimulator
{
public:
    void stiLoc(int, int);
    void switchState();
    void shiftRight(int);
    void shiftLeft(int);

};

class SimpleCXDecoder : public Flyintel
{
public:
    std::array<int, 16> sortingHat(char*);
    std::queue<int> findBump();
    void clean();
private:
    std::array<int, 16> eb;

};

typedef std::tuple<int, int, BYTE> LEDpacket;

class SimpleCXMonitor
{
public:
    SimpleCXMonitor();
    void init();
    void flush();
    void showBump(std::queue<int>);
private:
    max7219 chip;
    std::array<LEDpacket, 16> EB2Monitor;
};

#define SCX_MODEL_H
#endif
