#include "CXmodel.h"

using namespace std;

CentralComplex::CentralComplex() : PB_HALF_FR(70), RING_PEI_FR(200), RING_PEN_FR(200)
{}

CentralComplex::keepState()
{
    SendMacroFreq("Ring_Neuron_PEI", 0);
    SendMacroFreq("Ring_Neuron_PEN", );
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", 0);

CentralComplex::switchState()
{
    SendMacroFreq("Ring_Neuron_PEI", 0);
    SendMacroFreq("Ring_Neuron_PEN", 0);
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", 0);
}

CentralComplex::shiftRight()
{
    SendMacroFreq("Ring_Neuron_PEI", 0);
    SendMacroFreq("Ring_Neuron_PEN", );
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", 0);
}

CentralComplex::shiftLeft()
{
    SendMacroFreq("Ring_Neuron_PEI", 0);
    SendMacroFreq("Ring_Neuron_PEN", );
    SendMacroFreq("half_pb_left", 0);
    SendMacroFreq("half_pb_right", 0);
}