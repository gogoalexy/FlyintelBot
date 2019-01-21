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

#include "pixycam.h"

using namespace std;

PixyCam::PixyCam () {
    this->FOOD = 1;
    this->TOXIC = 2;
}

PixyCam::PixyCam (int food_sig, int toxic_sig) {
    this->FOOD = food_sig;
    this->TOXIC = toxic_sig;
}

int PixyCam::vision_init() {
    int pixy_init_status = pixy.init();

  // Was there an error initializing pixy? //
    if(!pixy_init_status == 0) {
    // Error initializing Pixy //
        cout<<"pixy_init(): ";
        pixy_error(pixy_init_status);

        return pixy_init_status;
    }
    pixy.changeProg("color_connected_components");
    return pixy_init_status;
}

void PixyCam::refresh() {
    if(!foodQ.empty()) {
        foodQ = clearQ;
    }
    if(!toxicQ.empty()) {
        toxicQ = clearQ;
    }
}

void PixyCam::capture() {

	int  Block_Index;

  // Query Pixy for blocks //
	pixy.ccc.getBlocks();
  // Were blocks detected? //
	if (pixy.ccc.numBlocks)
	{
		for (Block_Index = 0; Block_Index < pixy.ccc.numBlocks; ++Block_Index)
	    {
        	if(pixy.ccc.blocks[Block_Index].m_signature == FOOD){
            	auto food = make_pair(pixy.ccc.blocks[Block_Index].m_width*pixy.ccc.blocks[Block_Index].m_height, pixy.ccc.blocks[Block_Index].m_x);
            	foodQ.push(food);
        	}else if(pixy.ccc.blocks[Block_Index].m_signature == TOXIC){
            	auto toxic = make_pair(pixy.ccc.blocks[Block_Index].m_width*pixy.ccc.blocks[Block_Index].m_height, pixy.ccc.blocks[Block_Index].m_x);
            	toxicQ.push(toxic);
        	}else{
            	continue;
        	}
	    }
	}
}

array<obj, 2> PixyCam::pick() {
    array<obj, 2> see;

    if(!foodQ.empty()) {
        see[0] = foodQ.top();
    }else{
        see[0] = make_pair(0, 0);
    }

    if(!toxicQ.empty()) {
        see[1] = toxicQ.top();
    }else{
        see[1] = make_pair(0, 0);
    }

    return see;
}

PixyCam::~PixyCam(){

    while(!foodQ.empty()){
        foodQ.pop();
    }
    while(!toxicQ.empty()){
        toxicQ.pop();
    }
}
