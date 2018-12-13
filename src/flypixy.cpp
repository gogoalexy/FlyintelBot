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
#include "wiringPi.h"
#include "connect_to_flysim.cpp"
#include "flyintel.h"
#include "DCmotor.h"
#include "Sharp_IR.h"
#include "HC_SR04.h"
#include "attention.h"
#include "sensefilter.h"

#define CENTER_X 154
#define LEFT_X 0
#define RIGHT_X 319

bool chkSPI = false;

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused){
  // On CTRL+C - abort! //
    run_flag = false;
}

char *Spikes = nullptr;

int main(int argc, char *argv[]){
	int n;
	unsigned int frame = 0;

	if(wiringPiSetup() == -1){
		return -1;
	}

	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(27, OUTPUT);

	HCSR04 rescue0(15, 16, 10000);
	SharpIR rescue1(0, 0);
	SharpIR rescue2(0, 1);
	DCmotor front(8, 9, 7, 0, 1, 26);
	DCmotor rear(22, 21, 3, 2, 23, 24);
	Attention pixy;
	Flyintel flyintel;
	string conf_file = "./network/network21.conf", pro_file = "./network/network21.pro";
	fstream fp;
	fp.open("Spikeslog.txt", ios::out);

/*
OutFile protocol:
frame: <int>
Ultra: <float>; IR: <float>, <float>
Pixy: <float>, <float>, <float>
<char>
*/

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

	if(!pixy.vision_init() == 0){
	    return -4;
	}

	int ErrorNumFromReadFile=ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;
	 //0: normal; -1: conf file reading error; -2: pro file reading error

	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(27, HIGH);
	delay(500);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(27, LOW);

	while(run_flag){

	//baseline stimuli
	SendDist(2000, 1);
	SendDist(2000, 2);
	SendDist(2000, 3);
	SendDist(2000, 4);

		pixy.capture();
	  	array<obj, 2> see;
	  	see = pixy.pick();
		cout<<"frame: "<<frame<<endl;
		fp<<"frame: "<<frame<<endl;

		front.velocity(500, 500);
		rear.velocity(500, 500);
		flyintel.refresh();
		LinearFilter lfc(CENTER_X, 20, 130);
		LinearFilter lfl(LEFT_X, 8, 90);
		LinearFilter lfr(RIGHT_X, 8, 90);

        float center = abs(see[0].second - CENTER_X);
        if (!center){
        	center = 1;
        }
        float sensor = see[0].first/center;
/*Note: try operator overload to output file and console in the same line*/

		unsigned int soundtime = rescue0.UsoundRange();
		if(soundtime < 875){
			SendDist(9000, 5);
		}else{
			SendDist(9000-(9000/500.0)*(soundtime-875), 5);
		}

		cout<<rescue1.IRrange()<<' '<<rescue2.IRrange()<<endl;
		cout<<"Ultra: "<<soundtime<<"; ";

		float irL = rescue1.IRrange();
		if(irL > 600){
			SendDist(9000, 6);
		}else{
			SendDist(9000-(9000/100.0)*(600-irL), 6);
		}

		float irR = rescue2.IRrange();
		if(irR > 600){
			SendDist(9000, 7);
		}else{
			SendDist(9000-(9000/100.0)*(600-irR), 7);
		}

		cout<<"IR: "<<irL<<", "<<irR<<endl;

		float objC = abs (lfc.FilterGen(center)*sensor);
		float objL = abs (lfl.FilterGen(center)*sensor);
		float objR = abs (lfr.FilterGen(center)*sensor);
		//SendDist(objC, 1);
		//SendDist(objL, 2);
		//SendDist(objR, 3);
		//SendDist(1200, 1);
		cout<<"Pixy: "<<objC<<", "<<objL<<", "<<objR<<endl;

		Spikes=ActiveSimGetSpike("600");
		//-3: connect error
		cout
		<<"receving\n"
		<<"Spikes:"<<endl<<Spikes<<endl;
		fp<<"Spikes: "<<Spikes<<endl;

		switch(flyintel.motorNeuron(flyintel.cstoi(Spikes))) {
			case 'F':
				cout<<'F'<<endl;
				digitalWrite(4, HIGH);
				front.stop();
				rear.stop();
				front.forward();
				rear.forward();
				digitalWrite(4, LOW);
				fp<<'F'<<endl;
				break;
			case 'B':
				cout<<'B'<<endl;
				digitalWrite(5, HIGH);
				front.stop();
				rear.stop();
				front.backward();
				rear.backward();
				digitalWrite(5, LOW);
				fp<<'B'<<endl;
				break;
			case 'L':
				cout<<'L'<<endl;
				digitalWrite(6, HIGH);
				front.stop();
				rear.stop();
				front.velocity(650, 650);
				front.left();
				rear.left();
				digitalWrite(6, LOW);
				fp<<'L'<<endl;
				break;
			case 'R':
				cout<<'R'<<endl;
				digitalWrite(10, HIGH);
				front.stop();
				rear.stop();
				front.velocity(650, 650);
				front.right();
				rear.right();
				digitalWrite(10, LOW);
				fp<<'R'<<endl;
				break;
			default:
				cout<<'S'<<endl;
				front.stop();
				rear.stop();
				delay(150);
				fp<<'S'<<endl;
		}

		frame++;
	}
	fp.close();
	return 0;
}
