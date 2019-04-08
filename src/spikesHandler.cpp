#include "spikesHandler.h"

using namespace std;

int SpikesHandler::cstoi(char* Spikes)
{
    int j=0, k=0, max;
    while(true){
        if(Spikes[j] == ' ')
        {
            k++;
            j++;
        }
        else if(Spikes[j] >= '0' && Spikes[j] <= '9')
        {
            spiketrain[k] = spiketrain[k]*10 + Spikes[j]-'0';
            j++;
        }
        else if(Spikes[j] == 'E')
        {
            this->maxDataBytes = k-1;
            return maxDataBytes;//array elements (count from 0)
        }
    }
}

void SpikesHandler::printSpikesLog(fstream& logFd)
{
    logFd<<"Spikes:"<<'\n';
    for(int i=0; i<maxDataBytes; ++i)
    {
        logFd<<spiketrain[i]<<' ';
    }
    logFd<<endl;
}

void SpikesHandler::clear()
{
    memset(spiketrain, 0, sizeof(spiketrain));
}
