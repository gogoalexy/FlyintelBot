#ifndef CONNECT_TO_FLYSIM_H

#include <vector>
#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include "cltcmd.h"

#define TotalSensor 9 //FS(4) + TS(4) + NPY(1) when building neural circuit in Hanitu rule

class TypeFreqModule
{
	//for storing information of Type=ChangeExtFreq in network.pro
	public:
		TypeFreqModule();
		~TypeFreqModule();
		
		std::string EventTime;
		std::string Type;
		std::string Label;
		std::string PopulationText;
		std::string Population;
		std::string Receptor;
		std::string FreqExtText;
		float FreqExt;
		std::string EndText;
};

class MacroModule
{
    public:
        MacroModule();
        ~MacroModule();

        std::vector<std::string> members;
        std::string GroupNameText;
        std::string GroupMemberText;
        std::string EndMemberText;
};

class ProFileModule
{
	public:
		ProFileModule();
		~ProFileModule();
		
		std::map<std::string, MacroModule> macro;
		std::string StartMacroHeader;
		std::string EndMacroHeader;
		//std::vector<TypeFreqModule> TypeFreq; //Type=ChangeExtFreq
		std::string TypeFreq;
		std::string EventTimeText;
		std::string TypeMem; //Type=ChangeMembraneNoise
};


static std::string ConfFile="";
static ProFileModule ProFile;
static int Round=0;

int ReadFile(const std::string ConfFilename, const std::string ProFilename);
void SendFreq(float, std::string);
void SendMacroFreq(float, std::string);
char *ActiveSimGetSpike(std::string RunTime);
char *GetChAry(std::string tmp);
void CloseSim();

#define CONNECT_TO_FLYSIM_H
#endif
