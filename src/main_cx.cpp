#include <signal.h>
#include <time.h>
#include <iostream>
#include <string>
#include <queue>
#include <wiringPi.h>
#include "connect_to_flysim.h"
#include "CXmodel.h"

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused)
{
  // On CTRL+C - abort! //
    run_flag = false;
    CloseSim();
}

char *Spikes = nullptr;

int main()
{
	if(wiringPiSetup() == -1)
	{
		cout<<"wiringPi initialization error"<<endl;
		return -3;
	}
	
	string conf_file = "./networks/CXstandard.conf", pro_file = "./networks/CXstandard.pro";

	CentralComplexStimulator CXsti;
	CentralComplexDecoder CXdecode;

    int ErrorNumFromReadFile=ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);

    while(run_flag)
    {
    	clock_t tik = clock();

		SendFreq("Ring_Neuron_PEN", 200);
		SendMacroFreq("_macro_7", 50);

    	Spikes=ActiveSimGetSpike("300");
    	cout
		<<"receving\n";
		//<<"Spikes:"<<endl<<Spikes<<endl;
        CXdecode.sortingHat(Spikes);
        queue<int> ans (CXdecode.findBump());
        while(!ans.empty())
        {
            cout<<ans.front()<<' ';
            ans.pop();
        }
        cout<<endl;
        CXdecode.clean();

        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }
    
    return 0;
}
