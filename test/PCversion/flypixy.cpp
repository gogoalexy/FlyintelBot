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
#include <cmath>
#include "connect_to_flysim.cpp"
#include "flyintel.h"

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused){
  // On CTRL+C - abort! //
    run_flag = false;
}

char *Spikes = nullptr;

int main(int argc, char *argv[]){
	int n;

	Flyintel flyintel;
	string conf_file = "network20.conf", pro_file = "network20.pro";
	fstream fp;
	fp.open("Spikeslog.txt", ios::out);

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

		//baseline stimuli
		SendDist(2000, 1);
		SendDist(2000, 2);
		SendDist(2000, 3);
		SendDist(2000, 4);
    	Spikes=ActiveSimGetSpike("500");

		switch(flyintel.motorNeuron(flyintel.cstoi(Spikes))) {
			case 'F':
				cout<<'F'<<endl;
				fp<<'F'<<endl;
				break;
			case 'B':
				cout<<'B'<<endl;
				fp<<'B'<<endl;
				break;
			case 'L':
				cout<<'L'<<endl;
				fp<<'L'<<endl;
				break;
			case 'R':
				cout<<'R'<<endl;
				fp<<'R'<<endl;
				break;
			default:
				cout<<'S'<<endl;
				fp<<'S'<<endl;
		}
		flyintel.refresh();
    }
	fp.close();
	return 0;
}
