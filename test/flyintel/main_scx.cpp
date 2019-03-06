#include <signal.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "connect_to_flysim.h"
#include "SCXmodel.h"

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
    int pastNew = -1;
    enum Actions{Stop, Forward, Backward, Left, Right};
    Actions state = Stop;

	SimpleCXStimulator CXsti;
	SimpleCXDecoder CXdecode;

    fstream fp;
    fp.open("Flyintel.log", ios::out);

    string conf_file = "network_scxhz.conf", pro_file = "network_scx.pro";
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
        if(round <= 10)
            state = Stop;
        else if(round <= 20)
        {
            state = Stop;
            newTarget = true;
        }
        else if(round <= 50)
            state = Forward;
        else if(round <= 160)
            state = Backward;
        else if(round <= 200)
            state = Stop;
        else
            state = Right;
        
        if(pastNew >= 0)
    	{
    	    cout<<"pastnew"<<pastNew<<'\n';
    	    CXsti.stiLoc(pastNew, 0);
    	    pastNew = -1;
    	    holdTarget = true;
    	}
    	else if(newTarget)
    	{
    	    //.......locate
    	    cout<<"newTar"<<'\n';
  	        CXsti.stiLoc(6, 100);
            newTarget = false;
            holdTarget = false;
            pastNew = 6;
    	}
    	else if(holdTarget)
    	{
    	    if(state == Stop)
    	    {
    	        cout<<"stop"<<'\n';
    	    }
    	    else if(state == Forward)
    	    {
    	        cout<<"straight"<<'\n';
    	    }
    	    else if(state == Backward)
    	    {
    	        cout<<"back"<<'\n';
    	    }
        	else if(state == Left)
    	    {
    	        cout<<"left"<<'\n';
    	        CXsti.shiftLeft(200);
    	    }
        	else if(state == Right)
            {
                cout<<"right"<<'\n';
                CXsti.shiftRight(200);
            }
        }
        else
        {
            cout<<"No sti"<<'\n';
        }

        Spikes = ActiveSimGetSpike("250");
    	cout
		<<"receving\n";
		cout<<"Spikes:"<<endl<<Spikes<<endl;
        auto tmp = CXdecode.sortingHat(Spikes);
        for(auto it = tmp.cbegin(); it != tmp.cend(); ++it)
           fp<<*it<<' ';
        
        fp<<endl;
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }
    fp.close();
    return 0;
}
