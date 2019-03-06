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
    array<int, 16> bump = {0};
    int max = cstoi(inSpikes);
    
    for(int i=2; i<max; i+=3)
    {
        if(spiketrain[i] <= 15)
        {
            bump.at(spiketrain[i]) += 1;
        }
    }

    for(auto it = bump.cbegin(); it != bump.cend(); ++it)
        cout<<*it<<' ';
        
    cout<<endl;
    return bump;
}

void SimpleCXDecoder::clean()
{
    refresh();
}
