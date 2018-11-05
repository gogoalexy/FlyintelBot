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
			case 0:
				motor.forward++;
				break;
			case 1:
				motor.backward++;
				break;
			case 2:
				motor.left++;
				break;
			case 3:
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
		decision.rbackward = motor.backward/decision.denom;
	   	decision.rleft = motor.left/decision.denom;
	   	decision.rright = motor.right/decision.denom;
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
