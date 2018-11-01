//***********************************************************************
//  This file is part of Berryant.
//
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at http://mozilla.org/MPL/2.0/.
//***********************************************************************
#ifndef DCMOTOR_H

#include <wiringPi.h>

using namespace std;

class DCmotor{
public:
	DCmotor(short, short, short, short, short, short);
	void forward();
	void backward();
	void left();
	void right();
	void stop();
	void velocity(short, short);
private:
	short motorIN1;
	short motorIN2;
	short motorIN3;
	short motorIN4;
	short enableA;
	short enableB;
};

#define DCMOTOR_H
#endif
