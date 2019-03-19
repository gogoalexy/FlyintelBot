#ifndef SCX_MODEL_H

#include <array>
#include <queue>
#include <string>
#include <iostream>
#include <tuple>
#include "connect_to_flysim.h"
#include "spikesHandler.h"
#include "max7219.h"

class SimpleCXStimulator
{
public:
    void stiLoc(int, int);
    void rmAllSti();
    void switchState();
    void shiftRight(int);
    void shiftLeft(int);

};

class SimpleCXDecoder
{
public:
    std::array<int, 16> sortingHat(const SpikesHandler&);
    std::queue<int> findBump();
    void clear();

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
