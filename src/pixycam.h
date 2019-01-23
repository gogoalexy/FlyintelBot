/*
 *	  This file is part of FlyintelBot.
 *    Copyright (C) 2019  Alex Huang-Yu Yao
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

#ifndef PIXYCAM_H

//#include <cstdio> //sprintf is used in pixy.h but not included lol
#include <iostream>
#include <utility>
#include <queue>
#include <array>
#include "libpixyusb2.h"

/*
 *==============================View Field===============================
 *
 *    (0, 0)------------------------------(315, 0)
 *          |    increasing x ->          |
 *          |                             |
 *          |                             |
 *          |                             |
 *          |  increasing y               |
 *          |    |                        |
 *          |    *                        |
 *          |                             |
 *          |                             |
 *          ------------------------------(315, 207)
 *      (0, 207)
 *
 * Reference: https://docs.pixycam.com/wiki/doku.php?id=wiki:v2:ccc_api
 *=======================================================================
 */

#define PIXY2_CENTER_X 158
#define PIXY2_LEFT_X 0
#define PIXY2_RIGHT_X 315

const int BLOCK_BUFFER_SIZE = 25;

typedef std::pair<int, int> Obj;
//Obj pair
//first => area;
//second => x;

class PixyCam 
{
public:
    PixyCam();
    PixyCam(int, int);
    int init();
    void refresh();
    void capture();
    std::array<Obj, 2> pickLarge();
    ~PixyCam();
private:
	Pixy2 pixy;
    struct Block blocks[BLOCK_BUFFER_SIZE];
    const int FOOD;
    const int TOXIC;
    std::queue< Obj, std::list<Obj> > foodQ;
    std::queue< Obj, std::list<Obj> > toxicQ;
    std::queue< Obj, std::list<Obj> > clearQ;
};

#define PIXYCAM_H
#endif
