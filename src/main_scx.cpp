#include <signal.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "connect_to_flysim.h"
#include "SCXmodel.h"
#include "max7219.h"

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
	SimpleCXMonitor CXled;
	CXled.init();

    //fstream fp;

    string conf_file = "./networks/network_scxhz.conf", pro_file = "./networks/network_scx.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);

    for(int round=0; round<1000; ++round)
    {
    	clock_t tik = clock();

        if(round <=10)
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
        CXled.flush();
        auto tmp = CXdecode.sortingHat(Spikes);
        auto ans (CXdecode.findBump());
        CXled.showBump(ans);
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }

    return 0;
}
