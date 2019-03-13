#include "SCXmodel.h"

using namespace std;

void SimpleCXStimulator::stiLoc(int loc, int fr)
{
    string neuron = "Exc" + to_string(loc);
    SendFreq(neuron, fr);
}

void SimpleCXStimulator::shiftRight(int fr)
{
    SendFreq("R_ring", fr);
}

void SimpleCXStimulator::shiftLeft(int fr)
{
    SendFreq("L_ring", fr);
}

//====================================================

array<int, 16> SimpleCXDecoder::sortingHat(char* inSpikes)
{
    eb = {0};
    int max = cstoi(inSpikes);
    
    for(int i=2; i<max; i+=3)
    {
        if(spiketrain[i] <= 15)
        {
            eb.at(spiketrain[i]) += 1;
        }

    }

    for(auto it = eb.cbegin(); it != eb.cend(); ++it)
        cout<<*it<<' ';
        
    cout<<endl;
    return eb;
}

queue<int> SimpleCXDecoder::findBump()
{
    int tmpMax = 0;
    queue<int> bump;
    for(auto index=0; index<eb.size(); ++index)
    {
        if(eb.at(index) > tmpMax)
        {
            tmpMax = eb.at(index);
            while(!bump.empty())
            {
                bump.pop();
            }
            bump.push(index);
        }
        else if(eb.at(index) != 0 && eb.at(index) == tmpMax)
        {
            bump.push(index);
        }
        else
	    {
            continue;
        }
    }
    return bump;
}

void SimpleCXDecoder::clean()
{
    refresh();
}

