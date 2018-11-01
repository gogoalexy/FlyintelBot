/*
//***********************************************************************
//  This file is part of Berryant.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//***********************************************************************
*/
#include "DCmotor.h"

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

/*For rp3 analog outpot is poorly supported, it's better to get an external DAC.*/
void DCmotor::velocity(short velocityL, short velocityR){
	pwmWrite(enableA, velocityL);
	pwmWrite(enableB, velocityR);
}
