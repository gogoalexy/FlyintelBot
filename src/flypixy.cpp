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
	pinMode(10, OUTPUT);

	HCSR04 rescue0(8, 10, 10000);
	SharpIR rescue1(0, 1);
	SharpIR rescue2(0, 2);
	DCmotor front(8, 9, 7, 0, 1, 26);
	DCmotor rear(2, 3, 12, 13, 23, 24);
	Attention pixy;
	Flyintel flyintel;
	string conf_file = "../network/network12_filter.conf", pro_file = "../network/network12_filter.pro";
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

	if(!pixy.vision_init() == 0){
	    return -4;
	}

	int ErrorNumFromReadFile=ReadFile(conf_file, pro_file);
	cout<<"ErrorNumFromReadFile="<<ErrorNumFromReadFile<<endl<<endl;
	 //0: normal; -1: conf file reading error; -2: pro file reading error

	digitalWrite(4, HIGH);
	digitalWrite(5, HIGH);
	digitalWrite(6, HIGH);
	digitalWrite(10, HIGH);
	delay(1500);
	digitalWrite(4, LOW);
	digitalWrite(5, LOW);
	digitalWrite(6, LOW);
	digitalWrite(10, LOW);

	while(run_flag){


		pixy.capture();
	  	array<obj, 2> see;
	  	see = pixy.pick();
		cout<<"frame: "<<frame<<endl;

		front.velocity(500, 500);
		rear.velocity(500, 500);

		LinearFilter lfc(CENTER_X, 2, 130);
		LinearFilter lfl(LEFT_X, 3, 90);
		LinearFilter lfr(RIGHT_X, 3, 90);

        float center = abs(see[0].second - CENTER_X);
        if (!center){
        	center = 1;
        }
        float sensor = see[0].first/center;

		SendDist(rescue0.UsoundRange(), 9);
		SendDist(rescue1.IRrange(), 10);
		SendDist(rescue2.IRrange(), 11);
		SendDist(abs( lfc.FilterGen(center)*sensor ), 5);
		SendDist(abs( lfl.FilterGen(center)*sensor ), 6);
		SendDist(abs( lfr.FilterGen(center)*sensor ), 7);
		Spikes=ActiveSimGetSpike("500");
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
				break;
			default:
				cout<<'S'<<endl;
				front.stop();
				rear.stop();
				delay(150);
		}

		frame++;
	}
	fp.close();
	return 0;
}
