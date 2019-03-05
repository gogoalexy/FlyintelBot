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

//=======================================

//-------------------------------------
//encoding: row*10 + column
//00, 01, 02, 03, 04, 05, 06, 07
//10, 11, 12, 13, 14, 15, 16, 17
//20, 21, 22, 23, 24, 25, 26, 27
//30, 31, 32, 33, 34, 35, 36, 37
//40, 41, 42, 43, 44, 45, 46, 47
//50, 51, 52, 43, 54, 55, 56, 57
//60, 61, 62, 63, 64, 65, 66, 67
//70, 71, 72, 73, 74, 75, 76, 77
//--------------------------------------
CentralComplexMonitor::CentralComplexMonitor()
    : EB2MonitorOdd
      {
        {0b00011000},
        {0b00001110},
        {0b00000011},
        {0b00000011},
        {0b00000011},
        {0b00000011},
        {0b00000011},
        {0b00001110},
        {0b00011000},
        {0b01110000},
        {0b11000000},
        {0b11000000},
        {0b11000000},
        {0b11000000},
        {0b11000000},
        {0b01110000},
      }
{}

void CentralComplexMonitor::init()
{        
    chip.setShutdown(EXIT_SHUTDOWN);
    chip.setDecode(BCD_DECODE_NONE);
    chip.setLimit(SCAN_LIMIT_NONE);
    chip.setBrightness(BRIGHTNESS_MAX);
    chip.setMatrix(defaultMatrixConfig);
}
