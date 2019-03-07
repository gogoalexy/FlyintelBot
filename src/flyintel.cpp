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

Flyintel::Flyintel(): MAX_SPIKES(STEP_TIME/MOTOR_REFRAC), RATE_THRESHOLD(0.3), turnSmooth(0.3), baseSmooth(0.5)
{
	count = {0, 0, 0, 0};
	decision = {0.0, 0.0, 0.0, 0.0, 0.0};
	turnConst = 100;
	preturnSpeed = 0;
	prebaseSpeed = 0;
}

int Flyintel::cstoi(char* Spikes)
{
	int j=0, k=0, max;
	while(true){
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


motor Flyintel::getMotor(int max)
{
	for(int i=2; i<max; i+=3)
	{
		switch(spiketrain[i])
		{
			case 94:
				count.forward++;
				break;
			case 100:
				count.backward++;
				break;
			case 106:
				count.left++;
				break;
			case 112:
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
		return make_pair(0x0, 0); //S
	}
	else if(decision.rforward>0.5)
	{
		return make_pair(0x1, short(1024*decision.rforward)); //F
	}
	else if(decision.rbackward>0.5)
	{
		return make_pair(0x2, short(1024*decision.rbackward)); //B
	}
	else if(decision.rleft>0.5)
	{
		return make_pair(0x4, short(1024*decision.rleft)); //L
	}
	else if(decision.rright>0.5)
	{
		return make_pair(0x8, short(1024*decision.rright)); //R
	}
	else
	{
		return make_pair(0x0, 0); //S
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

void Flyintel::refresh()
{
	memset(spiketrain, 0,sizeof(spiketrain));
	count.forward=0;
	count.backward=0;
	count.left=0;
	count.right=0;
}
