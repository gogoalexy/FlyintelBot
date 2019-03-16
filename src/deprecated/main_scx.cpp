#include <signal.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include "connect_to_flysim.h"
#include "SCXmodel.h"
#include "max7219.h"
#include "SPIadc.h"
#include "ADXL335.h"
#include "Sharp_IR.h"

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

    ADC mcp3008;
    mcp3008.initSPI(88, 0);
    ADXL335 accel(mcp3008, 3);
   	SharpIR rescue1(mcp3008, 0);
	SharpIR rescue2(mcp3008, 1);

	SimpleCXStimulator CXsti;
	SimpleCXDecoder CXdecode;
	SimpleCXMonitor CXled;
	CXled.init();

    fstream fp;
    fp.open("FlyintelBot.log", ios::out);

    string conf_file = "./networks/network30.conf", pro_file = "./networks/network30.pro";
    int ErrorNumFromReadFile = ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    Flyintel flyintel;

    signal(SIGINT, handle_SIGINT);

    for(int round=0; round<1000; ++round)
    {
    	clock_t tik = clock();
    	flyintel.refresh();
		SendFreq("random1", 1500);
		SendFreq("random2", 1500);
		SendFreq("random3", 1700);
		SendFreq("random4", 1700);
   
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

		float irL = rescue1.IRrange();
		if(irL > 400)
		{
			SendFreq("TS2", 9000);
		}
		else
		{
			SendFreq(9000-(9000/90.0)*(400-irL), 6);//negative issue
		}

		float irR = rescue2.IRrange();
		if(irR > 400)
		{
			SendFreq("TS3", 9000);
		}
		else
		{
			SendFreq("TS3", (int)(9000-(9000/90.0)*(400-irR)));
		}

		cout<<"IR: "<<irL<<", "<<irR<<endl;


        Spikes = ActiveSimGetSpike("250");
    	cout
	<<"receving\n";
//		cout<<"Spikes:"<<endl<<Spikes<<endl;
        CXled.flush();
        auto tmp = CXdecode.sortingHat(Spikes);
        motor motorNeuron = flyintel.getMotor(flyintel.cstoi(Spikes));
		char dir = motorNeuron.first;
		if(dir == 'S')
            state = Stop;
        else if(dir == 'F')
            state = Forward;
        else if(dir == 'B')
            state = Backward;
        else if(dir == 'L')
            state = Left;
        else if(dir == 'R')
            state = Right;

		int speed = motorNeuron.second;
        for(auto it=tmp.cbegin(); it!=tmp.cend(); ++it)
        {
            fp<<*it<<' ';
        }
        auto ans (CXdecode.findBump());
        CXled.showBump(ans);
        fp<<endl;
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }

    return 0;
}
