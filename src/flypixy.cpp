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
    digitalWrite(8, 0);
    digitalWrite(9, 0);
    digitalWrite(7, 0);
    digitalWrite(0, 0);
    digitalWrite(22, 0);
    digitalWrite(21, 0);
    digitalWrite(3, 0);
    digitalWrite(2, 0);
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

		//front.velocity(450, 450)
		//rear.velocity(450, 450);
		flyintel.refresh();

/*Note: try operator overload to output file and console in the same line*/

		unsigned int soundtime = rescue0.UsoundRange();
		if(soundtime < 875){
			SendDist(9000, 5);
		}else{
			SendDist(9000-(9000/500.0)*(soundtime-875), 5);
		}

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


		float dx = retina[0].second - CENTER_X;
		float area = retina[0].first;
		if(area > 4000){
			area = 4000;
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


		Spikes=ActiveSimGetSpike("600");
		//-3: connect error
		cout
		<<"receving\n"
		<<"Spikes:"<<endl<<Spikes<<endl;
		fp<<"Spikes: "<<Spikes<<endl;

		front.stop();
		rear.stop();
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		digitalWrite(6, LOW);
		digitalWrite(27, LOW);

		motor motorNeuron = flyintel.getMotor(flyintel.cstoi(Spikes));
		if(motorNeuron.first & 0x1){
			short speed = motorNeuron.second - 300;
			cout<<'F'<<endl;
			digitalWrite(4, HIGH);
			front.velocity(speed, speed);
			rear.velocity(speed, speed);
			front.forward();
			rear.forward();
			fp<<'F'<<endl;
		}else if(motorNeuron.first & 0x2){
			short speed = motorNeuron.second - 300;
			cout<<'B'<<endl;
			digitalWrite(5, HIGH);
			front.velocity(speed, speed);
			rear.velocity(speed, speed);
			front.backward();
			rear.backward();
			fp<<'B'<<endl;
		}else if(motorNeuron.first & 0x4){
			short speed = motorNeuron.second + 200;
			if(speed > 1024){ speed = 1024; }
			cout<<'L'<<endl;
			digitalWrite(6, HIGH);
			front.velocity(speed, speed);
			rear.velocity(speed, speed);
			front.left();
			rear.left();
			fp<<'L'<<endl;
		}else if(motorNeuron.first & 0x8){
			short speed = motorNeuron.second + 200;
			if(speed > 1024){ speed = 1024; }
			cout<<'R'<<endl;
			digitalWrite(27, HIGH);
			front.velocity(speed, speed);
			rear.velocity(speed, speed);
			front.right();
			rear.right();
			fp<<'R'<<endl;
		}else{
			cout<<'S'<<endl;
			front.stop();
			rear.stop();
			fp<<'S'<<endl;
		}
		/*switch(flyintel.getMotor(flyintel.cstoi(Spikes))) {
			case 'F':
				cout<<'F'<<endl;
				digitalWrite(4, HIGH);
				front.forward();
				rear.forward();
				fp<<'F'<<endl;
				break;
			case 'B':
				cout<<'B'<<endl;
				digitalWrite(5, HIGH);
				front.backward();
				rear.backward();
				fp<<'B'<<endl;
				break;
			case 'L':
				cout<<'L'<<endl;
				digitalWrite(6, HIGH);
				front.velocity(650, 650);
				front.left();
				rear.left();
				fp<<'L'<<endl;
				break;
			case 'R':
				cout<<'R'<<endl;
				digitalWrite(27, HIGH);
				front.velocity(650, 650);
				front.right();
				rear.right();
				fp<<'R'<<endl;
				break;
			default:
				cout<<'S'<<endl;
				front.stop();
				rear.stop();
				fp<<'S'<<endl;
		}
		*/
	}
	fp.close();
	return 0;
}
