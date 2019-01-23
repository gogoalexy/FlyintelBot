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
#include <wiringPi.h>
#include "connect_to_flysim.cpp"
#include "flyintel.h"
#include "DCmotor.h"
#include "Sharp_IR.h"
#include "HC_SR04.h"
#include "attention.h"
//#include "sensefilter.h"

#define CENTER_X 154
#define LEFT_X 0
#define RIGHT_X 319

bool chkSPI = false;

using namespace std;

static bool run_flag = true;
void handle_SIGINT(int unused){
  // On CTRL+C - abort! //
    run_flag = false;
    digitalWrite(2, 0);
    digitalWrite(3, 0);
    digitalWrite(4, 0);
    digitalWrite(5, 0);
    digitalWrite(22, 0);
    digitalWrite(21, 0);
    digitalWrite(27, 0);
    digitalWrite(25, 0);
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
	DCmotor Mleft(22, 21, 27, 25, 1, 26);
	DCmotor Mright(2, 3, 4, 5, 23, 24);
	Attention pixy;
	//LinearFilter lfc(CENTER_X, 1, 100);
	//LinearFilter lfl(LEFT_X, 1, 60);
	//LinearFilter lfr(RIGHT_X, 1, 60);
	Flyintel flyintel;
	string conf_file = "./network/network21.conf", pro_file = "./network/network21.pro";
	fstream fp;
	fp.open("FlyintelBot.log", ios::out);

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

	while(run_flag){

		//baseline stimuli
		SendDist(1500, 1);
		SendDist(1500, 2);
		SendDist(1500, 3);
		SendDist(1500, 4);

		++frame;

		pixy.refresh();
		pixy.capture();
	  	array<obj, 2> retina;
	  	retina = pixy.pick();
		cout<<"frame: "<<frame<<endl;
		fp<<"frame: "<<frame<<endl;

		flyintel.refresh();

/*Note: try operator overload to output file and console in the same line*/

		unsigned int soundtime = rescue0.UsoundRange();
		if(soundtime < 875){
			SendDist(9500, 5);
		}else{
			SendDist(9500-(9500/500.0)*(soundtime-875), 5);
		}

		cout<<"Ultra: "<<soundtime<<"; ";


		float irL = rescue1.IRrange();
		if(irL > 600){
			SendDist(9000, 6);
		}else{
			SendDist(9000-(9000/90.0)*(600-irL), 6);
		}

		float irR = rescue2.IRrange();
		if(irR > 600){
			SendDist(9000, 7);
		}else{
			SendDist(9000-(9000/90.0)*(600-irR), 7);
		}

		cout<<"IR: "<<irL<<", "<<irR<<endl;


		float dx = retina[0].second - CENTER_X;
		float area = retina[0].first;
		if(area > 5000){
			area = 5000;
		}else if(area >= 1000 && area < 2000){
			area = 2000;
		}
		if(dx > 120){
			SendDist(0, 8);
			SendDist(0, 9);
			SendDist(area, 10);
		}else if(dx < -120){
			SendDist(0, 8);
			SendDist(area, 9);
			SendDist(0, 10);
		}else{
			SendDist(area, 8);
			SendDist(0, 9);
			SendDist(0, 10);
		}

		cout<<"area="<<area<<", dx="<<dx<<endl;


		Spikes=ActiveSimGetSpike("500");
		//-3: connect error
		cout
		<<"receving\n"
		<<"Spikes:"<<endl<<Spikes<<endl;
		fp<<"Spikes: "<<Spikes<<endl;


		vmotor motorNeuron = flyintel.getSpeed(flyintel.cstoi(Spikes));
		int vleft = motorNeuron.first;
		int vright = motorNeuron.second;
		if(vleft < 0){
			vleft = -vleft;
			if(vleft > 400){
				vleft = 400;
			}
			Mleft.velocity(vleft, vleft);
			Mleft.reverse();
		}else{
			if(vleft > 400){
				vleft = 400;
			}
			Mleft.velocity(vleft, vleft);
			Mleft.proceed();
		}
		
		if(vright < 0){
			vright = -vright;
			if(vright > 400){
				vright = 400;
			}
			Mright.velocity(vright, vright);
			Mright.reverse();
		}else{
			if(vright > 400){
				vright = 400;
			}
			Mright.velocity(vright, vright);
			Mright.proceed();
		}

		
	}
	fp.close();
	return 0;
}
