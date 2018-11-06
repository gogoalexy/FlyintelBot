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

#ifndef ATTENTION_H

#include <cstdio> //sprintf is used in pixy.h but not included lol
#include <iostream>
#include <utility>
#include <queue>
#include <array>
#include "pixy.h"

#define BLOCK_BUFFER_SIZE 25

typedef std::pair<int, int> obj;
/*
struct Object {
    float key_area;
    float horizontal;
}
*/
class Attention {
public:
    Attention();
    Attention(int, int);
    int vision_init();
    void refresh();
    void capture();
    std::array<obj, 2> pick();
    ~Attention();
private:
    int FOOD;
    int TOXIC;
    struct Block blocks[BLOCK_BUFFER_SIZE];
    std::priority_queue< obj, std::vector<obj>, std::greater<obj> > foodQ;
    std::priority_queue< obj, std::vector<obj>, std::greater<obj> > toxicQ;
    std::priority_queue< obj, std::vector<obj>, std::greater<obj> > clearQ;
};

#define ATTENTION_H
#endif
