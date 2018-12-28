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

#ifndef FLYINTEL_H

#include <iostream>
#include <cstring>
#include <utility>
#include <cmath>

#define MOTOR_REFRAC 10
#define STEP_TIME 50
#define V_MAX 1024
#define V_MIN 400

struct Container{
	float forward;
	float backward;
	float left;
	float right;
	float noise;
	float conflict;
};

struct Ratio{
	float denom;
	float rforward;
	float rbackward;
	float rleft;
	float rright;
};

typedef std::pair<unsigned char, short> motor;
typedef std::pair<int, int> vmotor;

class Flyintel {
public:
Flyintel();
int cstoi(char*);
motor getMotor(int);
vmotor getSpeed(int);
void refresh();

private:
Container count;
Ratio decision;
int spiketrain[500];
const int MAX_SPIKES;
//const int speedDynamic;
int turnConst;
int preturnSpeed;
int prebaseSpeed;

};

#define FLYINTEL_H
#endif
