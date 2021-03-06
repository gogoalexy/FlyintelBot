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

DCmotor::DCmotor(short IN1, short IN2, short IN3, short IN4, short enA, short enB)
 : motorIN1(IN1), motorIN2(IN2), motorIN3(IN3), motorIN4(IN4), enableA(enA), enableB(enB)
{
	pinMode(motorIN1, OUTPUT);
	pinMode(motorIN2, OUTPUT);
	pinMode(motorIN3, OUTPUT);
	pinMode(motorIN4, OUTPUT);
	pinMode(enableA, PWM_OUTPUT);
	pinMode(enableB, PWM_OUTPUT);
}

DCmotor::DCmotor(short IN1, short IN2, short IN3, short IN4)
 : motorIN1(IN1), motorIN2(IN2), motorIN3(IN3), motorIN4(IN4)
{  
	pinMode(motorIN1, OUTPUT);
	pinMode(motorIN2, OUTPUT);
	pinMode(motorIN3, OUTPUT);
	pinMode(motorIN4, OUTPUT);
}

int DCmotor::soft_init(short enableA, short enableB)
{
	this->enableA = enableA;
    this->enableB = enableB;
	int pwmcreate = softPwmCreate (enableA, 0, 100);
	if (pwmcreate)
	{
		return -8;
	}
	pwmcreate = softPwmCreate (enableB, 0, 100);
	if (pwmcreate)
	{
		return -8;
	}
}

void DCmotor::forward()
{
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::backward()
{
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

void DCmotor::left()
{
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::right()
{
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

void DCmotor::forward(int v)
{
    velocity(v, v);
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::backward(int v)
{
    velocity(v, v);
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

void DCmotor::left(int v)
{
    velocity(v, v);
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::right(int v)
{
    velocity(v, v);
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

void DCmotor::stop()
{
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 0);
}

/*left/right grouping*/
void DCmotor::proceed()
{
	digitalWrite(motorIN1, 1);
	digitalWrite(motorIN2, 0);
	digitalWrite(motorIN3, 1);
	digitalWrite(motorIN4, 0);
}

void DCmotor::reverse()
{
	digitalWrite(motorIN1, 0);
	digitalWrite(motorIN2, 1);
	digitalWrite(motorIN3, 0);
	digitalWrite(motorIN4, 1);
}

/*hardware PWM*/
void DCmotor::velocity(int velocity1, int velocity2)
{
	pwmWrite(enableA, velocity1);
	pwmWrite(enableB, velocity2);
}

/*software PWM*/
void DCmotor::softvelocity(int velocity1, int velocity2)
{
	softPwmWrite (enableA, velocity1);
	softPwmWrite (enableB, velocity2);
}
