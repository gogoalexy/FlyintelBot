#include "connect_to_flysim.h"

using namespace std;

TypeFreqModule::TypeFreqModule()
{
    EventTime="EventTime 0";
    Type="Type=ChangeExtFreq";
    Label="Label=#1#";
    PopulationText="Population:";
    Population="";
    Receptor="Receptor: AMPA";
    FreqExtText="FreqExt=";
    FreqExt=0;
    EndText="EndEvent";
}

TypeFreqModule::~TypeFreqModule()
{}

MacroModule::MacroModule()
{
    GroupNameText="GroupName:";
    GroupMemberText="GroupMembers:";
    EndMemberText="EndGroupMembers";
}

MacroModule::~MacroModule()
{}

ProFileModule::ProFileModule()
{
    StartMacroHeader="DefineMacro";
    EndMacroHeader="EndDefineMacro";
    EventTimeText="EventTime";
}

ProFileModule::~ProFileModule()
{}

int ReadFile(const string ConfFilename, const string ProFilename)
{
    ifstream ReadCon;
    //read conf file
    ReadCon.open(ConfFilename);
    if(!ReadCon){
        cout<<"Fail to read: "<<ConfFilename<<endl;
        return -1;
    }
    while(!ReadCon.eof())
    {
        ConfFile+=ReadCon.get(); 
    }
    ReadCon.close();
    
    ConfFile[ConfFile.size() - 1] = '\0';
    //end of reading conf file

    //read pro file
    ifstream ReadPro;
    ReadPro.open(ProFilename);
    if(!ReadPro){
        cout<<"Fail to read: "<<ProFilename<<endl;
        return -2;
    }
    
    string tmp="";
    bool isFreq = false;
    string tmp2line[2];
    
    while(!ReadPro.eof())
    {
        getline(ReadPro, tmp);

        //Parse macro
        if(tmp.find(ProFile.StartMacroHeader) != string::npos)
        {
            bool newMacro = false;
            cout<<"Start parsing macro..."<<endl;
            while(true)
            {
                getline(ReadPro, tmp);
                if(tmp.find(ProFile.EndMacroHeader) != string::npos)
                {
                    tmp2line[0].clear();
                    tmp2line[1].clear();
                    break;
                }
                    
                if(tmp.find("GroupName") != string::npos)
                {
                    tmp2line[0]=tmp;//add 1st line
                    getline(ReadPro, tmp);
                    if(tmp.find("GroupMembers") != string::npos)
                    {
                        newMacro = true;
                        tmp2line[1]=tmp;
                    }
                    else
                    {
                        continue;
                    }
                }
                else if(tmp.find("EndGroupMembers") != string::npos)
                {
                    newMacro = false;
                    tmp2line[0].clear();
                    tmp2line[1].clear();
                    continue;
                }
                
                if(newMacro)
                {
                    int found = tmp2line[0].find_first_of(":");
                    tmp2line[0].erase(tmp2line[0].begin(), tmp2line[0].begin()+found+1);
                    found = tmp2line[1].find_first_of(":");
                    tmp2line[1].erase(tmp2line[1].begin(), tmp2line[1].begin()+found+1);

                    MacroModule tmpMacro;
                    string name;
                    for(int i=0; i<tmp2line[1].length(); ++i)
                    {
                        while(tmp2line[1].at(i) != ',')
                        {
                            name.push_back(tmp2line[1].at(i));
                            ++i;
                            if(i>=tmp2line[1].length())
                                break;
                        }
                        tmpMacro.members.push_back(name);
                        name.clear();
                    }
                    ProFile.macro.insert( pair<string, MacroModule>(tmp2line[0],tmpMacro) );
                }

            }
        }

        //Parse stimuli
        if(tmp.find(ProFile.EventTimeText) != string::npos)
        {
            tmp2line[0]=tmp;//add 1st line
            getline(ReadPro, tmp);
            if(tmp.find("Type")!=string::npos)
                tmp2line[1]=tmp;//add 2nd line
            else
                continue;

            if(tmp.find("ChangeExtFreq") != string::npos)//find Type=ChangeExtFreq
            {
                ProFile.TypeFreq = ProFile.TypeFreq+'\n'+tmp2line[0]+'\n'+tmp2line[1]+'\n';
                tmp2line[0].clear();
                tmp2line[1].clear();
                isFreq = true;
            }
            else if(tmp.find("ChangeMembraneNoise") != string::npos)
            {
                //FindFreq=0;
                ProFile.TypeMem = ProFile.TypeMem+'\n'+tmp2line[0]+'\n'+tmp2line[1]+'\n';
                tmp2line[0].clear();
                tmp2line[1].clear();
            }
            continue;

        }
        else if((tmp.find("EndEvent") != string::npos)&&(isFreq))
        {
            isFreq = false;
            continue;
        }
        
        if(!isFreq && tmp[0]>' ' && tmp[0]!='%')
        {
            ProFile.TypeMem=ProFile.TypeMem+tmp+"\n";
        }   
        else if(isFreq && tmp[0]>' ' && tmp[0]!='%')
        {
            ProFile.TypeFreq = ProFile.TypeFreq+tmp+"\n";
        }

    }
    ReadPro.close();
    
    //end of reading pro file
    #ifdef DEBUG_FILE
        for(auto it = ProFile.macro.cbegin(); it != ProFile.macro.cend(); ++it)
        {
            for(auto vit = it->second.members.cbegin(); vit != it->second.members.cend(); ++vit)
            {
                cout << it->first << " " << *vit << "\n";
            }
        }
        cout<<ProFile.TypeFreq<<endl;
        cout<<ProFile.TypeMem<<endl;
    #endif

    return 0;
}

void SendFreq(string SensorID, float DisFreq)
{
    TypeFreqModule typeFreq;
    string tmpPro;
    
    tmpPro = typeFreq.EventTime + '\n'
            + typeFreq.Type + '\n'
            + typeFreq.Label + '\n'
            + typeFreq.PopulationText + SensorID + '\n'
            + typeFreq.Receptor + '\n'
            + typeFreq.FreqExtText + to_string(DisFreq) + '\n'
            + typeFreq.EndText + '\n' + '\n';

    ProFile.TypeFreq += tmpPro;
};

void SendMacroFreq(string MacroID, float DisFreq)
{
    MacroModule macroContent = ProFile.macro.at(MacroID);
    
    for(int i=0; i<macroContent.members.size(); i++)
    {
        SendFreq(macroContent.members.at(i), DisFreq);
    }
}

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
        return (char*)"-3";
    }
    //port -1
    CltInit();
    //port -2
    CltInit();
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

    if(Round==0)
    {
        char *ForSendConf=nullptr;
        ForSendConf=GetChAry(ConfFile);
        //strcpy(ForSendConf, ConfFile.c_str());    
        //ForSendConf[ConfFile.size()]='\0';
        CltCmd(cmd7,defaultconfname,ForSendConf);
        CltCmd(cmd3,defaultconfname,ForSendConf);
        #ifdef DEBUG
            cout<<"ADD_WORM-1"<<'\n';
        #endif
        Round++;
        ProString+=ProFile.TypeMem;
    }

        ProString += ProFile.TypeFreq;
        ProFile.TypeFreq.clear();

        #ifdef DEBUG
            cout<<"ProFile checking"<<'\n';
            cout<<ProString<<endl;
        #endif

    char *ForSendPro=GetChAry(ProString);
    //strcpy(ForSendPro, ProString.c_str());
    //ForSendPro[ProString.size()]='\0';    
    CltCmd(cmd7,defaultproname,ForSendPro);
    CltCmd(cmd5,defaultproname,(char*)"0");//DO_EVENTS, pro
    //char *SetRunTime=nullptr;
    //strcpy(SetRunTime, RunTime.c_str());
    return CltCmd(cmd6,opt8,GetChAry(RunTime));
}

char *GetChAry(string tmp) //char *GetChAry(char *argv)
{
    char buf32[32], *s2=nullptr;

    s2 = (char *) malloc(tmp.size()+1);
    strcpy(s2,tmp.c_str());
    s2[tmp.size()]='\0';

    return s2;
}

void CloseSim()
{
    CltClose();
}
