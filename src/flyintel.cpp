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
	count = {0, 0, 0, 0, 0, 0};
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

motor Flyintel::getMotor(int max) {
	for(int i=2; i<max; i+=3){
		switch(spiketrain[i]){
			case 5:
				count.forward++;
				break;
			case 11:
				count.backward++;
				break;
			case 17:
				count.left++;
				break;
			case 23:
				count.right++;
				break;
			default:
				count.noise++;
		}
	}
	/*
	if(count.forward != 0)
		motor.conflict++;
	if(count.backward != 0)
		motor.conflict++;
	if(count.left != 0)
		motor.conflict++;
	if(count.right != 0)
		motor.conflict++;
	*/
	decision.denom = count.forward+count.backward+count.right+count.left;
	if(decision.denom == 0)
		decision.denom = 1;
	if(decision.denom){
	    	decision.rforward = count.forward/decision.denom;
		std::cout<<decision.rforward<<";";
		decision.rbackward = count.backward/decision.denom;
		std::cout<<decision.rbackward<<";";
	   	decision.rleft = count.left/decision.denom;
		std::cout<<decision.rleft<<";";
	   	decision.rright = count.right/decision.denom;
		std::cout<<decision.rright<<";"<<endl;
	}

	if(decision.rforward<=0.5 && decision.rbackward<=0.5 && decision.rleft<=0.5 && decision.rright<=0.5){
		return make_pair(0x0, 0); //S
	}else if(decision.rforward>0.5){
		return make_pair(0x1, short(1024*decision.rforward)); //F
	}else if(decision.rbackward>0.5){
		return make_pair(0x2, short(1024*decision.rbackward)); //B
	}else if(decision.rleft>0.5){
		return make_pair(0x4, short(1024*decision.rleft)); //L
	}else if(decision.rright>0.5){
		return make_pair(0x8, short(1024*decision.rright)); //R
	}
}

void Flyintel::refresh() {
	memset(spiketrain, 0,sizeof(spiketrain));
	count.forward=0;
	count.backward=0;
	count.left=0;
	count.right=0;
	count.noise=0;
	count.conflict=0;
}
