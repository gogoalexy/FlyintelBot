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

//===================================================

SimpleCXMonitor::SimpleCXMonitor()
{
    EB2Monitor[0] = make_tuple(0, 1, 0b00011000);
    EB2Monitor[1] = make_tuple(0, 1, 0b00001110);
    EB2Monitor[2] = make_tuple(0, 1, 0b00000011);
    EB2Monitor[3] = make_tuple(1, 3, 0b00000011);
    EB2Monitor[4] = make_tuple(3, 4, 0b00000011);
    EB2Monitor[5] = make_tuple(4, 6, 0b00000011);
    EB2Monitor[6] = make_tuple(6, 7, 0b00000011);
    EB2Monitor[7] = make_tuple(6, 7, 0b00001110);
    EB2Monitor[8] = make_tuple(6, 7, 0b00011000);
    EB2Monitor[9] = make_tuple(6, 7, 0b01110000);
    EB2Monitor[10] = make_tuple(6, 7, 0b11000000);
    EB2Monitor[11] = make_tuple(4, 6, 0b11000000);
    EB2Monitor[12] = make_tuple(3, 4, 0b11000000);
    EB2Monitor[13] = make_tuple(1, 3, 0b11000000);
    EB2Monitor[14] = make_tuple(0, 1, 0b11000000);
    EB2Monitor[15] = make_tuple(0, 1, 0b01110000);
}

void SimpleCXMonitor::init()
{
    if(chip.max7219Setup(1, 1000000) == -1)
    {
        exit(1);
    }
    chip.setShutdown(EXIT_SHUTDOWN);
    chip.setDecode(BCD_DECODE_NONE);
    chip.setLimit(SCAN_LIMIT_NONE);
    chip.setTest(EXIT_DISPLAY_TEST);
    chip.setBrightness(BRIGHTNESS_MAX);
    chip.flush();
}

void SimpleCXMonitor::flush()
{
    chip.flush();
}

void SimpleCXMonitor::showBump(std::queue<int> location)
{
    while(!location.empty())
    {
        auto bump = location.front();
        cout<<"bump: "<<bump<<' ';
        location.pop();
        auto startROW = get<0>(EB2Monitor.at(bump));
        auto endROW = get<1>(EB2Monitor.at(bump));
        cout<<startROW<<','<<endROW<<endl;
        for(int i=startROW; i<=endROW; ++i)
        {
            chip.setROW(i, get<2>(EB2Monitor.at(bump)));
        }
    }
}
