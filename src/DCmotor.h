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
 
#ifndef DCMOTOR_H

#include <wiringPi.h>
#include <softPwm.h>

class DCmotor{
public:
	DCmotor(short, short, short, short, short, short);
	DCmotor(short, short, short, short);
	void forward();
	void backward();
	void left();
	void right();
	void stop();
	void velocity(int, int);
	int soft_init();
	void softvelocity(int, int);
	void proceed();
	void reverse();
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
