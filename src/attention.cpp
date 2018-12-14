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

#include "attention.h"

using namespace std;

Attention::Attention () {
    this->FOOD = 1;
    this->TOXIC = 2;
}

Attention::Attention (int food_sig, int toxic_sig) {
    this->FOOD = food_sig;
    this->TOXIC = toxic_sig;
}

int Attention::vision_init() {
    int pixy_init_status = pixy_init();

  // Was there an error initializing pixy? //
    if(!pixy_init_status == 0) {
    // Error initializing Pixy //
        cout<<"pixy_init(): ";
        pixy_error(pixy_init_status);

        return pixy_init_status;
    }
}

void Attention::refresh() {
    if(!foodQ.empty()) {
        foodQ = clearQ;
    }
    if(!toxicQ.empty()) {
        toxicQ = clearQ;
    }
}

void Attention::capture() {
// Wait for new blocks to be available //
    while(!pixy_blocks_are_new()) {} 

    // Get blocks from Pixy //
    int blocks_copied = pixy_get_blocks(BLOCK_BUFFER_SIZE, &blocks[0]);

    if(blocks_copied < 0) {
      // Error: pixy_get_blocks //
        cout<<"pixy_get_blocks(): ";
        pixy_error(blocks_copied);
    }

    for(int i=0; i!= blocks_copied; ++i) {
        if(blocks[i].signature == FOOD){
            auto food = make_pair(blocks[i].width*blocks[i].height, blocks[i].x);
            foodQ.push(food);
        }else if(blocks[i].signature == TOXIC){
            auto toxic = make_pair(blocks[i].width*blocks[i].height, blocks[i].x);
            toxicQ.push(toxic);
        }else{
            continue;
        }
    }

}

array<obj, 2> Attention::pick() {
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

Attention::~Attention(){
    pixy_close();
    while(!foodQ.empty()){
        foodQ.pop();
    }
    while(!toxicQ.empty()){
        toxicQ.pop();
    }
}
