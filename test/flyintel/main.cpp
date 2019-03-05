/*
 *	  This file is part of FlyintelBot.
 *    Copyright (C) 2018  Alex Huang-Yu Yao
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <signal.h>
#include <iostream>
#include <string>
#include <queue>
#include <time.h>
#include <cmath>
#include "connect_to_flysim.h"
#include "flyintel.h"
#include "CXmodel.h"

#define NUM_NEURONS 61

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused){
  // On CTRL+C - abort! //
    run_flag = false;
    CloseSim();
    exit(0);
}

char *Spikes = nullptr;

int main(int argc, char *argv[]){
	int n = 0;

	Flyintel flyintel;
	CentralComplexStimulator CXsti;
	CentralComplexDecoder CXdecode;
	string conf_file = "CXstandard.conf", pro_file = "CXstandard.pro";
	fstream fp;
	fp.open("Speed.log", ios::out);

	//argument
	if(argc == 1){
	}else if(argc >= 2 && argv[1] == "-f"){
	    conf_file = argv[2];
	    pro_file = argv[3];
	}else{
	    cout<<"Unrecognizable arguments\n"
	    <<"Use default file path"<<endl;
	}

	signal(SIGINT, handle_SIGINT);


	int ErrorNumFromReadFile=ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;
	 //0: normal; -1: conf file reading error; -2: pro file reading error

	while(run_flag){
		++n;
		clock_t tik = clock();
		//baseline stimuli
		SendFreq("Ring_Neuron_PEN", 200);
		SendMacroFreq("_macro_7", 50);
		//SendFreq(50, "_macro_3");

    	Spikes=ActiveSimGetSpike("300");
    	cout
		<<"receving\n"
		<<"Spikes:"<<endl<<Spikes<<endl;
        CXdecode.sortingHat(Spikes);
        queue<int> ans (CXdecode.findBump());
        while(!ans.empty())
        {
            cout<<ans.front()<<' ';
            ans.pop();
        }
        cout<<endl;
        CXdecode.clean();

/*
		motor motorNeuron = flyintel.getMotor(flyintel.cstoi(Spikes));
		if(motorNeuron.first & 0x1){
			short speed = motorNeuron.second - 350;
			cout<<'F'<<endl;
			fp<<n<<' '<<vleft<<' '<<vright<<' '<<'F'<<endl;
		}else if(motorNeuron.first & 0x2){
			short speed = motorNeuron.second - 350;
			cout<<'B'<<endl;
			fp<<n<<' '<<vleft<<' '<<vright<<' '<<'B'<<endl;
		}else if(motorNeuron.first & 0x4){
			short speed = motorNeuron.second + 200;
			if(speed > 1024){ speed = 1024; }
			cout<<'L'<<endl;
			fp<<n<<' '<<vleft<<' '<<vright<<' '<<'L'<<endl;
		}else if(motorNeuron.first & 0x8){
			short speed = motorNeuron.second + 200;
			if(speed > 1024){ speed = 1024; }
			cout<<'R'<<endl;
			fp<<n<<' '<<vleft<<' '<<vright<<' '<<'R'<<endl;
		}else{
			cout<<'S'<<endl;
			fp<<n<<' '<<vleft<<' '<<vright<<' '<<'S'<<endl;
		}

		flyintel.refresh();
		*/
		clock_t tok = clock();
cout<<"time:"<<(tok-tik)/(double)CLOCKS_PER_SEC<<endl;
    }
	fp.close();
	return 0;
}
