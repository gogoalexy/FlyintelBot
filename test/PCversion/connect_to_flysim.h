#ifndef CONNECT_TO_FLYSIM_H

#include <vector>
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
		int Population; //Population: Exc1
		std::string Receptor;
		std::string FreqExtText;
		float FreqExt;
		std::string EndText;
};

class TypeMacroModule
{
    public:
        TypeMacroModule();
        ~TypeMacroModule();
        
        std::string StartHeader;
        std::string GroupNameText;
        std::string GroupName;
        std::string GroupMemberText;
        std::string GroupMember;
        std::string EndMember;
        std::string EndHeader;
};

class ProFileModule
{
	public:
		ProFileModule();
		~ProFileModule();
		
		std::vector<TypeFreqModule> TypeFreq; //Type=ChangeExtFreq
		std::string FirstEventTime;
		std::string TypeMem; //Type=ChangeMembraneNoise
};

class FindMacroModule
{
    public:
        FindMacroModule();
        ~FindMacroModule();

};

static std::string ConfFile="";
static std::string ProFileComplete="";
static ProFileModule ProFile;
static int Round=0;

int ReadFile(const std::string ConfFilename, const std::string ProFilename);
void SendFreq(float DisFreq, int SensorID);
void SendFreq(float, std::string);
char *ActiveSimGetSpike(std::string RunTime);
char *GetChAry(std::string tmp);
void CloseSim();

#define CONNECT_TO_FLYSIM_H
#endif
