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
#include "spikesHandler.h"

#define MOTOR_REFRAC 10
#define STEP_TIME 50
#define V_MAX 500
#define V_MIN 200

struct Container
{
    float forward;
    float backward;
    float left;
    float right;
};

struct Ratio
{
    float denom;
    float rforward;
    float rbackward;
    float rleft;
    float rright;
};

typedef std::pair<unsigned char, short> motor;
typedef std::pair<int, int> vmotor;

class Flyintel
{
public:
    Flyintel();
    void sortingHat(const SpikesHandler&);
    motor getMotor();
    void clear();

protected:
    Container count;
    Ratio decision;
};

#define FLYINTEL_H
#endif
