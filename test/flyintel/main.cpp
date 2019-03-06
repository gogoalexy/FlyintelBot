#include <signal.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <tuple>
#include <array>
#include "connect_to_flysim.h"
#include "CXmodel.h"

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused)
{
   //On CTRL+C - abort! //
    run_flag = false;
    CloseSim();
}

char *Spikes = nullptr;


int main()
{
    bool holdTarget = false;
    bool newTarget = false;
    string pastNew = "";
    enum Actions{Stop, Forward, Backward, Left, Right};
    Actions state = Stop;

	CentralComplexStimulator CXsti;
	CentralComplexDecoder CXdecode;

    fstream fp;
    fp.open("Flyintel.log", ios::out);

    string conf_file = "CXstandard.conf", pro_file = "CXstandard.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);

    for(int round=0; round<1000; ++round)
    {
    	clock_t tik = clock();
    	/*
    	int move=0;
    	cin>>newTarget>>move;
	if(move == 0)    	
		state = Stop;
	if(move == 1)    	
		state = Forward;
	if(move == 2)    	
		state = Backward;
	if(move == 3)    	
		state = Left;
	if(move == 4)    	
		state = Right;
*/
        if(round <= 3)
            state = Stop;
        else if(round == 4)
        {
            state = Stop;
            newTarget = true;
        }
        else if(round <= 10)
            state = Forward;
        else if(round <= 20)
            state = Backward;
        else if(round <= 50)
            state = Stop;
        else
            state = Right;
        
        if(!pastNew.empty())
    	{
    	    cout<<"pastnew"<<pastNew<<'\n';
    	    SendMacroFreq(pastNew, 0);
    	    pastNew.clear();
    	    holdTarget = true;
    	}
    	else if(newTarget)
    	{
    	    //.......locate
    	    cout<<"newTar"<<'\n';
    	    string pos;
  	        CXsti.switchState();
   		    SendFreq("Ring_Neuron_PEN", 200);
            SendMacroFreq("_macro_6", 50);
            newTarget = false;
            holdTarget = false;
            pastNew = "_macro_6";
    	}
    	else if(holdTarget)
    	{
    	    if(state == Stop)
    	    {
    	        cout<<"stop"<<'\n';
    	        //CXsti.switchState();
    	        CXsti.keepState();
    	    }
    	    else if(state == Forward)
    	    {
    	        cout<<"straight"<<'\n';
    	        //CXsti.switchState();
    	        CXsti.keepState();
    	    }
    	    else if(state == Backward)
    	    {
    	        cout<<"back"<<'\n';
    	        //CXsti.switchState();
    	        CXsti.keepState();
    	    }
        	else if(state == Left)
    	    {
    	        cout<<"left"<<'\n';
    	        //CXsti.switchState();
    	        CXsti.shiftLeft();
    	    }
        	else if(state == Right)
            {
                cout<<"right"<<'\n';
                CXsti.shiftRight();
            }
        }
        else
        {
            cout<<"No sti"<<'\n';
        }

        Spikes = ActiveSimGetSpike("250");
    	cout
		<<"receving\n";
		//cout<<"Spikes:"<<endl<<Spikes<<endl;
        auto tmp = CXdecode.sortingHat(Spikes);
        //for(auto it = tmp.cbegin(); it != tmp.cend(); ++it)
         //   fp<<*it<<' ';
        
        //fp<<endl;
        queue<int> ans (CXdecode.findBump());
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }
    //fp.close();
    return 0;
}
