#ifndef CONNECT_TO_FLYSIM_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#define TotalSensor 9 //FS(4) + TS(4) + NPY(1) when building neural circuit in Hanitu rule

using namespace std;

class TypeFreqModule
{
	//for storing information of Type=ChangeExtFreq in network.pro
	public:
		TypeFreqModule();
		~TypeFreqModule();
		
		string EventTime;
		string Type;
		string Label;
		string PopulationText;
		int Population; //Population: Exc1
		string Receptor;
		string FreqExtText;
		float FreqExt;
		string EndText;
};

class ProFileModule
{
	public:
		ProFileModule();
		~ProFileModule();
		
		vector<TypeFreqModule> TypeFreq; //Type=ChangeExtFreq
		string FirstEventTime;
		string TypeMem; //Type=ChangeMembraneNoise
};

static string ConfFile="";
static string ProFileComplete="";
static ProFileModule ProFile;
static int Round=0;

int ReadFile(const string ConfFilename, const string ProFilename);
void SendDist(float DisFreq, int SensorID);
char *ActiveSimGetSpike(string RunTime);
char *GetChAry(string tmp);
void CloseSim();

#define CONNECT_TO_FLYSIM_H
#endif
