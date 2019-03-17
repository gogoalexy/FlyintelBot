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
			this->maxDataByte = k-1;
			return maxDataByte;//array elements (count from 0)
		}
	}
}
