#include "CXmodel.h"

using namespace std;

CentralComplexStimulator::CentralComplexStimulator() : PB_HALF_FR(70), RING_PEI_FR(200), RING_PEN_FR(200)
{}

void CentralComplexStimulator::keepState()
{
    SendMacroFreq("Ring_Neuron_PEI", 0);
    SendMacroFreq("Ring_Neuron_PEN", RING_PEN_FR);
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", 0);
}

void CentralComplexStimulator::switchState()
{
    SendMacroFreq("Ring_Neuron_PEI", 0);
    SendMacroFreq("Ring_Neuron_PEN", 0);
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", 0);
}

void CentralComplexStimulator::shiftRight()
{
    SendMacroFreq("Ring_Neuron_PEI", RING_PEI_FR);
    SendMacroFreq("Ring_Neuron_PEN", 0);
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", PB_HALF_FR);
}

void CentralComplexStimulator::shiftLeft()
{
    SendMacroFreq("Ring_Neuron_PEI", RING_PEI_FR);
    SendMacroFreq("Ring_Neuron_PEN", 0);
    SendMacroFreq("half_pb_left", PB_HALF_FR);
    SendMacroFreq("half_pb_right", 0);
}

//====================================================

CentralComplexDecoder::CentralComplexDecoder()
    : EIP2EB
    {
        {0, 1, 17, -1},
	    {1, 17, 10, -1},
	    {1, 2, 10, -1},
	    {2, 10, 11, -1},
	    {2, 3, 11, -1},
	    {3, 11, 12, -1},
	    {3, 4, 12, -1},
	    {4, 12, 13, -1},
	    {4, 5, 13, -1},
	    {5, 13, 14, -1},
	    {5, 6, 14, -1},
	    {6, 14, 15, -1},
	    {6, 7, 15, -1},
	    {7, 15, 16, -1},
	    {7, 0, 16, -1},
	    {0, 16, 17, -1}
    }
     , SIZE_POPULATION(10)
{}

void CentralComplexDecoder::sortingHat(char* inSpikes)
{
    array<int, 18> sortedEIP = {0};
    int max = cstoi(inSpikes);
    
    for(int i=2; i<max; i+=3)
	{
	    if(spiketrain[i] < 18*SIZE_POPULATION)
	    {
	    //cout<<" !"<<spiketrain[i];
            sortedEIP.at(spiketrain[i] / SIZE_POPULATION) += 1;
        }
	}
	
    for(int j=0; j<16; ++j)
    {
        for(int k=0; k<3; ++k)
        {
            int activity = sortedEIP.at(EIP2EB[j][k]);
            activityEB.at(j) += activity;
        }
    }
    for(auto it = activityEB.cbegin(); it != activityEB.cend(); ++it)
        cout<<*it<<' ';
        
    cout<<endl;
}

queue<int> CentralComplexDecoder::findBump()
{
    int tmpMax = 0;
    queue<int> bump;
    for(auto index=0; index<activityEB.size(); ++index)
    {
        if(activityEB.at(index) > tmpMax)
        {
            tmpMax = activityEB.at(index);
            while(!bump.empty())
            {
                bump.pop();
            }
            bump.push(index);
        }
        else if(activityEB.at(index) != 0 && activityEB.at(index) == tmpMax)
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

void CentralComplexDecoder::clean()
{
    activityEB.fill(0);
    refresh();
}

//====================================================

//-------------------------------------
//odd: 6 LEDs (3*2)
//even: 4 LEDs (2*2)
//std::tuple<int START_ROW, int END_ROW, BYTE CONTENTS>
//--------------------------------------
CentralComplexMonitor::CentralComplexMonitor()
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

void CentralComplexMonitor::init()
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

void CentralComplexMonitor::flush()
{
    chip.flush();
}

void CentralComplexMonitor::showBump(std::queue<int> location)
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
