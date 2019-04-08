#ifndef SPIKES_HANDLER_H

#include <cstring>
#include <fstream>

//library class for unified spikes data transform
class SpikesHandler
{
public:
    int cstoi(char*);
    void printSpikesLog(std::fstream&);
    void clear();

    int spiketrain[7000];
    int maxDataBytes;
};

#define SPIKES_HANDLER_H
#endif
