#include <signal.h>
#include <time.h>
#include <iostream>
#include <string>
#include <queue>
#include <wiringPi.h>
#include "connect_to_flysim.h"
#include "CXmodel.h"
#include "max7219.h"

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
        //CentralComplexMonitor CXled;
       max7219 led;
       led.max7219Setup(1, 1000000);

    int ErrorNumFromReadFile=ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;

    signal(SIGINT, handle_SIGINT);
    //CXled.init();

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
        //CXled.showBump(ans);
led.setTest(ENTER_DISPLAY_TEST);
        cout<<endl;
        CXdecode.clean();
delay(100);
        clock_t tok = clock();
        cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }

    return 0;
}
