#ifndef SCX_MODEL_H

#include <array>
#include <queue>
#include <string>
#include <iostream>
#include "connect_to_flysim.h"
#include "spikesHandler.h"
#ifdef PI
    #include <tuple>
    #include "max7219.h"
#endif

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

#ifdef PI
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
#endif

#define SCX_MODEL_H
#endif
