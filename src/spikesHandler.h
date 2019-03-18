#ifndef SPIKES_HANDLER_H

#include <cstring>

class SpikesHandler
{
public:
    int cstoi(char*);
    void clear();

    int spiketrain[7000];
    int maxDataBytes;
};

#define SPIKES_HANDLER_H
#endif
