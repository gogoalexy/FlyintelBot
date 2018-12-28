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

#include "DCmotor.h"

using namespace std;

DCmotor::DCmotor(short motorIN1, short motorIN2, short motorIN3, short motorIN4, short enableA, short enableB){
    this->motorIN1 = motorIN1;
    this->motorIN2 = motorIN2;
    this->motorIN3 = motorIN3;
    this->motorIN4 = motorIN4;
    this->enableA = enableA;
    this->enableB = enableB;
	pinMode(motorIN1, OUTPUT);
	pinMode(motorIN2, OUTPUT);
	pinMode(motorIN3, OUTPUT);
	pinMode(motorIN4, OUTPUT);
	pinMode(enableA, PWM_OUTPUT);
	pinMode(enableB, PWM_OUTPUT);
}

void DCmotor::forward(){
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::backward(){
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

void DCmotor::left(){
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::right(){
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

void DCmotor::stop(){
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 0);
}

/*left/right grouping*/
void DCmotor::proceed(){
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::reverse(){
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

/*For rp3 analog outpot is poorly supported, it's better to get an external DAC.*/
void DCmotor::velocity(short velocityL, short velocityR){
	pwmWrite(enableA, velocityL);
	pwmWrite(enableB, velocityR);
}
