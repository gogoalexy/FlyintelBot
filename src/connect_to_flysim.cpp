#include "cltcmd.h"
#include "connect_to_flysim.h"

//#define DEBUG
#ifdef DEBUG
	#define DEBUG(x) cout<<__FILE__<<" "<<__LINE__<<" "<<__PRETTY_FUNCTION__<<" : "<<x<<endl
#endif

TypeFreqModule::TypeFreqModule()
{
	EventTime="EventTime 0";
	Type="Type=ChangeExtFreq";
	Label="Label=#1#";
	PopulationText="Population: Exc";
	Population=0;
	Receptor="Receptor: AMPA";
	FreqExtText="FreqExt=";
	FreqExt=0;
	EndText="EndEvent";
};

TypeFreqModule::~TypeFreqModule()
{};

ProFileModule::ProFileModule()
{
	FirstEventTime="EventTime 0";
};

ProFileModule::~ProFileModule()
{};

int ReadFile(const string ConfFilename, const string ProFilename)
{
	ifstream ReadCon;
	//reading conf file
	ReadCon.open(ConfFilename);
	if(!ReadCon)
	{
		cout<<"Fail to read: "<<ConfFilename<<endl;
		return -1;
	}
	while(!ReadCon.eof())
		ConfFile+=ReadCon.get(); 
	ReadCon.close();
	
	ConfFile[ConfFile.size()-1]='\0';
	
	//end of reading conf file

	//reading pro file
	ifstream ReadPro;
	ReadPro.open(ProFilename);
	if(!ReadPro)
	{
		cout<<"Fail to read: "<<ProFilename<<endl;
		return -2;
	}
	
	string tmp="";
	int FindFreq=0;
	string tmp2line[2];
	
	while(!ReadPro.eof())
	{	
		getline(ReadPro, tmp);
		
		if(tmp.find(ProFile.FirstEventTime)!=string::npos) 
		{
			tmp2line[0]=tmp;//add 1st line
			getline(ReadPro, tmp);
			if(tmp.find("Type")!=string::npos)
				tmp2line[1]=tmp;//add 2nd line
			else
				continue;
				
			if(tmp.find("ChangeExtFreq")!=string::npos)//find Type=ChangeExtFreq
			{
				FindFreq=1;
				tmp2line[0]="";
				tmp2line[1]="";
			}
			continue;
		}
		else if((tmp.find("EndEvent")!=string::npos)&&(FindFreq==1))
		{
			FindFreq=0;
			continue;
		}
		
		if(FindFreq==1)
		{
			
			if(tmp.find("Population")!=string::npos)
			{
				int found=tmp.find_first_of("Exc");
				string tmpnum="";
				for(int c=found+3; tmp[c]>' '; c++)
					tmpnum+=tmp[c];
				
				TypeFreqModule tmpTypeFreq;
				tmpTypeFreq.Population=atoi(tmpnum.c_str());
				ProFile.TypeFreq.insert(ProFile.TypeFreq.end(), tmpTypeFreq);
			}
		}
		else if(FindFreq==0 && tmp[0]>' ')
		{
			ProFile.TypeMem=ProFile.TypeMem+tmp2line[0]+tmp2line[1]+tmp+"\n";
			tmp2line[0]="";
			tmp2line[1]="";
		}
	}
	ReadPro.close();
	
	//end of reading pro file
		
	/*for(int i=0; i<ProFile.TypeFreq.size(); i++)
	{
		cout
		<<ProFile.TypeFreq[i].EventTime<<endl
		<<ProFile.TypeFreq[i].Type<<endl
		<<ProFile.TypeFreq[i].Label<<endl
		<<ProFile.TypeFreq[i].PopulationText
		<<ProFile.TypeFreq[i].Population<<endl
		<<ProFile.TypeFreq[i].Receptor<<endl
		<<ProFile.TypeFreq[i].FreqExtText
		<<ProFile.TypeFreq[i].FreqExt<<endl
		<<ProFile.TypeFreq[i].EndText<<endl<<endl;
	}
	
	cout<<ProFile.TypeMem<<endl;*/
	
	return 0;
};

void SendDist(float DisFreq, int SensorID)
{
	#ifdef DEBUG
		DEBUG(ProFile.TypeFreq[SensorID-1].FreqExt);
	#endif

	ProFile.TypeFreq[SensorID-1].FreqExt=DisFreq;
};
char *ActiveSimGetSpike(string RunTime)
{
	if(CltInit()<0) //connect error
	{
		/*cout
		<<"Flysim error!"<<endl
		<<"Please check whether flysim is running or not."<<endl
		<<"You can change port and restart if flysim is running"<<endl
		<<"or just restart flysim."
		<<endl;*/
		return "-3";			
	}
	CltInit();
	#ifdef DEBUG
		DEBUG("open port -1");
	#endif
	CltInit();
	#ifdef DEBUG
		DEBUG("open port -2");
	#endif
	string ProString="";
	
	char cmd1[]="FILE_WRITE";
	char cmd2[]="FILE_READ";//read simulator output
	char cmd3[]="ADD_WORM";
	char cmd4[]="DEL_WORM";
	char cmd5[]="DO_EVENTS";
	char cmd6[]="DATA_READ";
	char cmd7[]="FILE_SEND";
	char opt6[]="Spikes_Header";
	char opt7[]="Spikes";
	char opt8[]="Spikes_Cont";
	char defaultconfname[]="network.conf";
	char defaultproname[]="network.pro";
	
	#ifdef DEBUG
		DEBUG(Round);
	#endif
	if(Round==0)
	{
		char *ForSendConf=nullptr;
		ForSendConf=GetChAry(ConfFile);
		//strcpy(ForSendConf, ConfFile.c_str());	
		//ForSendConf[ConfFile.size()]='\0';
		CltCmd(cmd7,defaultconfname,ForSendConf);
		CltCmd(cmd3,defaultconfname,ForSendConf);
		#ifdef DEBUG
			DEBUG("ADD_WORM-1");
		#endif
		Round++;
		ProString+=ProFile.TypeMem;
	}
	
	
	for(int i=0; i<ProFile.TypeFreq.size(); i++)
	{
		ProString=
		ProString+ProFile.TypeFreq[i].EventTime+"\n"
		+ProFile.TypeFreq[i].Type+"\n"
		+ProFile.TypeFreq[i].Label+"\n"
		+ProFile.TypeFreq[i].PopulationText
		+to_string(ProFile.TypeFreq[i].Population)+"\n"
		+ProFile.TypeFreq[i].Receptor+"\n"
		+ProFile.TypeFreq[i].FreqExtText
		+to_string(ProFile.TypeFreq[i].FreqExt)+"\n"
		+ProFile.TypeFreq[i].EndText+"\n"+"\n";
	}

        #ifdef DEBUG
		DEBUG("ProFile checking");
		cout<<ProString<<endl;                
        #endif

	char *ForSendPro=GetChAry(ProString);
	//strcpy(ForSendPro, ProString.c_str());
	//ForSendPro[ProString.size()]='\0';	
	CltCmd(cmd7,defaultproname,ForSendPro);
	CltCmd(cmd5,defaultproname,"0");//DO_EVENTS, pro
	//char *SetRunTime=nullptr;
	//strcpy(SetRunTime, RunTime.c_str());
	return CltCmd(cmd6,opt8,GetChAry(RunTime));
};

char *GetChAry(string tmp) //char *GetChAry(char *argv)
{
  char buf32[32], *s2=nullptr;
  
  s2 = (char *) malloc(tmp.size()+1);
  strcpy(s2,tmp.c_str());
  s2[tmp.size()]='\0';

  return s2;
};
