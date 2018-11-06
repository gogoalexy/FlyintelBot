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

#include <cstring>

struct Container{
	short forward;
	short backward;
	short left;
	short right;
	short noise;
	short conflict;
};

struct Ratio{
	float denom;
	float rforward;
	float rbackward;
	float rleft;
	float rright;
};

class Flyintel {
public:
Flyintel();
int cstoi(char*);
char motorNeuron(int);
void refresh();

private:
Container motor;
Ratio decision;
int spiketrain[300];

};

#define FLYINTEL_H
#endif
