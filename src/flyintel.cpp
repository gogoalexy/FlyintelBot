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

Flyintel::Flyintel():MAX_SPIKES(STEP_TIME/MOTOR_REFRAC), RATE_THRESHOLD(0.3), turnSmooth(0.3), baseSmooth(0.5)
{
	count = {0, 0, 0, 0};
	decision = {0.0, 0.0, 0.0, 0.0, 0.0};
	turnConst = 100;
	preturnSpeed = 0;
	prebaseSpeed = 0;
//	neurogroup = {0};
//	led.init(128, 1);
}

int Flyintel::cstoi(char* Spikes)
{
	int j=0, k=0, max;
	while(1){
		if(Spikes[j] == ' ')
		{
			k++;
			j++;
		}
		else if(Spikes[j] >= '0' && Spikes[j] <= '9')
		{
			spiketrain[k] = spiketrain[k]*10 + Spikes[j]-'0';
			j++;
		}
		else if(Spikes[j] == 'E')
		{
			this->maxspikes = k-1;
			return maxspikes;//array elements (count from 0)
		}
	}
}
/*
void NeuroMonitor::sortinghat(int max)
{
	for(int i=2; i<max; i+=3){
		int tmp = spiketrain[i];
		if(tmp > 40)
		{
			continue;
		}
		else if(tmp > 25)
		{
			switch(tmp)
			{
				case 26 ... 27:
					neurogroup.rsensorF++;
					continue;
				case 28 ... 30:
					neurogroup.FInh++;
					continue;
				case 31 ... 32:
					neurogroup.rsensorBL++;
					continue;
				case 33 ... 35:
					neurogroup.BLInh++;
					continue;
				case 36 ... 37:
					neurogroup.rsensorBR++;
					continue;
				case 38 ... 40:
					neurogroup.BRInh++;
					continue;
			}
		}
		else if(tmp == 24 || tmp == 25)
		{
			neurogroup.globalInh++;
		}
		else if(tmp >= 18)
		{
			switch(tmp)
			{
				case 18 ... 19:
					neurogroup.fsensorR++;
					continue;
				case 20 ... 22:
					neurogroup.pmR++;
					continue;
				case 23:
					neurogroup.motorR++;
					continue;
			}
		}
		else if(tmp >= 12)
		{
			switch(tmp)
			{
				case 12 ... 13:
					neurogroup.fsensorL++;
					continue;
				case 14 ... 16:
					neurogroup.pmL++;
					continue;
				case 17:
					neurogroup.motorL++;
					continue;
			}
		}
		else if(tmp >= 6)
		{
			switch(tmp)
			{
				case 6 ... 7:
					neurogroup.fsensorB++;
					continue;
				case 8 ... 10:
					neurogroup.pmB++;
					continue;
				case 11:
					neurogroup.motorB++;
					continue;
			}
		}
		else if(tmp >= 0)
		{
			switch(tmp)
			{
				case 0 ... 1:
					neurogroup.fsensorF++;
					continue;
				case 2 ... 4:
					neurogroup.pmF++;
					continue;
				case 5:
					neurogroup.motorF++;
					continue;
			}
		}
	}

	count = {motorF, motorB, motorL, motorR};
}
*/
motor Flyintel::getMotor(int max)
{
	for(int i=2; i<max; i+=3)
	{
		switch(spiketrain[i])
		{
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
				;
		}
	}

	decision.denom = count.forward+count.backward+count.right+count.left;
	if(decision.denom == 0)
		decision.denom = 1;
	if(decision.denom)
	{
	    	decision.rforward = count.forward/decision.denom;
		std::cout<<decision.rforward<<";";
		decision.rbackward = count.backward/decision.denom;
		std::cout<<decision.rbackward<<";";
	   	decision.rleft = count.left/decision.denom;
		std::cout<<decision.rleft<<";";
	   	decision.rright = count.right/decision.denom;
		std::cout<<decision.rright<<";"<<endl;
	}

	if(decision.rforward<=0.5 && decision.rbackward<=0.5 && decision.rleft<=0.5 && decision.rright<=0.5)
	{
		return make_pair('S', 0); //S
	}
	else if(decision.rforward>0.5)
	{
		short speed = 700*decision.rforward;
		if(speed < 500 && speed > 350)
			speed = 500;
		return make_pair('F', speed); //F
	}
	else if(decision.rbackward>0.5)
	{
		short speed = 700*decision.rbackward;
		if(speed < 500 && speed > 350)
			speed = 500;
		return make_pair('B', speed); //B
	}
	else if(decision.rleft>0.5)
	{
		short speed = 700*decision.rleft;
		if(speed < 500 && speed > 350)
			speed = 500;
		return make_pair('L', speed); //L
	}
	else if(decision.rright>0.5)
	{
		short speed = 700*decision.rright;
		if(speed < 500 && speed > 350)
			speed = 500;
		return make_pair('R', speed); //R
	}
	else
	{
		return make_pair('S', 0); //S
	}
}

vmotor Flyintel::getSpeed(int max)
{
	for(int i=2; i<max; i+=3)
	{
		switch(spiketrain[i])
		{
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
				;
		}
	}

	int SpikeThreshold = RATE_THRESHOLD * MAX_SPIKES;
	float forwardRate = 0, backwardRate = 0, leftRate = 0, rightRate = 0;
	if(count.forward > SpikeThreshold)
	{
		forwardRate = (float)count.forward / (float)MAX_SPIKES;
	}
	if(count.backward > SpikeThreshold)
	{
		backwardRate = (float)count.backward / (float)MAX_SPIKES;
	}
	if(count.left > SpikeThreshold)
	{
		leftRate = (float)count.left / (float)MAX_SPIKES;
	}
	if(count.right > SpikeThreshold)
	{
		rightRate = (float)count.right / (float)MAX_SPIKES;
	}

	float turnAct = turnConst * ( leftRate - rightRate );
	float baseAct = ( forwardRate - backwardRate ) * V_MAX;

	int turnSpeed = turnSmooth * turnAct + (1 - turnSmooth) * preturnSpeed;
	int baseSpeed =  baseSmooth * baseAct + (1 - baseSmooth) * prebaseSpeed;

	preleftRate = leftRate;
	prerightRate = rightRate;
	preforwardRate = forwardRate;
	prebackwardRate = backwardRate;
	preturnSpeed = turnSpeed;
	prebaseSpeed = baseSpeed;


	if(baseSpeed >= 0)
	{
		return make_pair(3*(baseSpeed - turnSpeed), 3*(baseSpeed + turnSpeed));//enlarge
	}
	else if(baseSpeed < 0)
	{
		return make_pair(3*(baseSpeed + turnSpeed), 3*(baseSpeed - turnSpeed));
	}
	else
	{
		return make_pair(0, 0);
	}

}
/*
vmotor Flyintel::getSpeed(int max)
{
	for(int i=2; i<max; i+=3)
	{
		switch(spiketrain[i])
		{
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
				;
		}
	}

	int SpikeThreshold = RATE_THRESHOLD * MAX_SPIKES;
	float forwardRate = 0, backwardRate = 0, leftRate = 0, rightRate = 0;
	if(count.forward > SpikeThreshold)
	{
		forwardRate = (float)count.forward / (float)MAX_SPIKES;
	}
	if(count.backward > SpikeThreshold)
	{
		backwardRate = (float)count.backward / (float)MAX_SPIKES;
	}
	if(count.left > SpikeThreshold)
	{
		leftRate = (float)count.left / (float)MAX_SPIKES;
	}
	if(count.right > SpikeThreshold)
	{
		rightRate = (float)count.right / (float)MAX_SPIKES;
	}

	float turnAct = turnConst * ( leftRate - rightRate );
	float baseAct = ( forwardRate - backwardRate ) * V_MAX;
	
	int turnSpeed = turnSmooth * turnAct + (1 - turnSmooth) * preturnSpeed;
	int baseSpeed =  baseSmooth * baseAct + (1 - baseSmooth) * prebaseSpeed;
	
	preleftRate = leftRate;
	prerightRate = rightRate;
	preforwardRate = forwardRate;
	prebackwardRate = backwardRate;
	preturnSpeed = turnSpeed;
	prebaseSpeed = baseSpeed;


	if(baseSpeed >= 0)
	{
		return make_pair(2*(baseSpeed - turnSpeed), 2*(baseSpeed + turnSpeed));//enlarge
	}
	else if(baseSpeed < 0)
	{
		return make_pair(2*(baseSpeed + turnSpeed), 2*(baseSpeed - turnSpeed));
	}
	else
	{
		return make_pair(0, 0);
	}

}
*/
void Flyintel::refresh()
{
	memset(spiketrain, 0,sizeof(spiketrain));
	count.forward=0;
	count.backward=0;
	count.left=0;
	count.right=0;
}
