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

#include "flyintel.h"

using namespace std;

Flyintel::Flyintel() {
	motor = {0, 0, 0, 0, 0, 0};
	decision = {0.0, 0.0, 0.0, 0.0, 0.0};
}

int Flyintel::cstoi(char* Spikes) {
	int j=0, k=0, max;
	while(1){
		if(Spikes[j] == ' '){
			k++;
			j++;
		}else if(Spikes[j] >= '0' && Spikes[j] <= '9'){
			spiketrain[k] = spiketrain[k]*10 + Spikes[j]-'0';
			j++;
		}else if(Spikes[j] == 'E'){
			return max = k-1;//array elements (count from 0)
		}
	}
}

char Flyintel::motorNeuron(int max) {
	for(int i=2; i<max; i+=3){
		switch(spiketrain[i]){
			case 5:
				motor.forward++;
				break;
			case 11:
				motor.backward++;
				break;
			case 17:
				motor.left++;
				break;
			case 23:
				motor.right++;
				break;
			default:
				motor.noise++;
		}
	}
	
	if(motor.forward != 0)
		motor.conflict++;
	if(motor.backward != 0)
		motor.conflict++;
	if(motor.left != 0)
		motor.conflict++;
	if(motor.right != 0)
		motor.conflict++;

	decision.denom = motor.forward+motor.backward+motor.right+motor.left;
	if(decision.denom == 0)
		decision.denom = 1;
	if(decision.denom){
	    	decision.rforward = motor.forward/decision.denom;
		std::cout<<decision.rforward<<";";
		decision.rbackward = motor.backward/decision.denom;
		std::cout<<decision.rbackward<<";";
	   	decision.rleft = motor.left/decision.denom;
		std::cout<<decision.rleft<<";";
	   	decision.rright = motor.right/decision.denom;
		std::cout<<decision.rright<<";"<<endl;
	}
	
	if(decision.rforward<=0.5 && decision.rbackward<=0.5 && decision.rleft<=0.5 && decision.rright<=0.5){
		return 'S';
	}else if(decision.rforward>0.5){
		return 'F';
	}else if(decision.rbackward>0.5){
		return 'B';
	}else if(decision.rleft>0.5){
		return 'L';
	}else if(decision.rright>0.5){
		return 'R';
	}
}

void Flyintel::refresh() {
	memset(spiketrain, 0,sizeof(spiketrain));
	motor.forward=0;
	motor.backward=0;
	motor.left=0;
	motor.right=0;
	motor.noise=0;
	motor.conflict=0;
}
