#ifndef SPIKES_HANDLER_H

class SpikesHandler
{
public:
    int cstoi(char*);
protected:
    int spiketrain[7000];
    int maxDataByte;
};

#define SPIKES_HANDLER_H
#endif
