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
	string conf_file = "./network/network12_filter.conf", pro_file = "./network/network12_filter.pro";
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
	delay(1500);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(27, LOW);

	while(run_flag){


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
		cout<<rescue0.UsoundRange()<<";";
		float sound = 2018 * exp(-pow((rescue0.UsoundRange()-1000), 2)/300);
		SendDist(sound, 9);
		fp<<"Ultra: "<<sound<<"; ";
		cout<<rescue1.IRrange()<<' '<<rescue2.IRrange()<<endl;
		cout<<"Ultra: "<<sound<<"; ";
		float ir1 = 2018 * exp(-pow((rescue1.IRrange()-1000), 2)/150);
		float ir2 = 2018 * exp(-pow((rescue2.IRrange()-1000), 2)/150);
		SendDist(ir1, 10);
		SendDist(ir2, 11);
		fp<<"IR: "<<ir1<<", "<<ir2<<endl;
		cout<<"IR: "<<ir1<<", "<<ir2<<endl;
		float objC = abs (lfc.FilterGen(center)*sensor);
		float objL = abs (lfl.FilterGen(center)*sensor);
		float objR = abs (lfr.FilterGen(center)*sensor);
		SendDist(objC, 5);
		SendDist(objL, 6);
		SendDist(objR, 7);
		fp<<"Pixy: "<<objC<<", "<<objL<<", "<<objR<<endl;
		cout<<"Pixy: "<<objC<<", "<<objL<<", "<<objR<<endl;
		Spikes=ActiveSimGetSpike("800");
		//-3: connect error
		cout
		<<"receving\n"
		<<"Spikes:"<<endl<<Spikes<<endl;

		switch(flyintel.motorNeuron(flyintel.cstoi(Spikes))) {
			case 'F':
				cout<<'F'<<endl;
				digitalWrite(4, HIGH);
				front.stop();
				rear.stop();
				front.forward();
				rear.forward();
				delay(150);
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
				delay(150);
				digitalWrite(5, LOW);
				fp<<'B'<<endl;
				break;
			case 'L':
				cout<<'L'<<endl;
				digitalWrite(6, HIGH);
				front.stop();
				rear.stop();
				front.left();
				rear.left();
				delay(200);
				digitalWrite(6, LOW);
				fp<<'L'<<endl;
				break;
			case 'R':
				cout<<'R'<<endl;
				digitalWrite(10, HIGH);
				front.stop();
				rear.stop();
				front.right();
				rear.right();
				delay(200);
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
