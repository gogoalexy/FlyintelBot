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

#include "pixycam.h"

using namespace std;

PixyCam::PixyCam(): pixy(), FOOD(1), TOXIC(2)
{
    cout<<"Default pixy signature tags."<<endl;
}

PixyCam::PixyCam(int food_sig, int toxic_sig): pixy(), FOOD(food_sig), TOXIC(toxic_sig)
{}

int PixyCam::init()
{
    int pixy_init_status = pixy.init();
  // Was there an error initializing pixy? //
    if(pixy_init_status < 0)
    {
    // Error initializing Pixy //
        cout<<"pixy.init(): Error "<<pixy_init_status<<endl;

        return pixy_init_status;
    }
    pixy.changeProg("color_connected_components");
    return pixy_init_status;
}

void PixyCam::refresh()
{
    if(!foodQ.empty())
    {
        foodQ = clearQ;
    }
    if(!toxicQ.empty())
    {
        toxicQ = clearQ;
    }
}

void PixyCam::capture()
{
    int  block_index;
    // Query Pixy for blocks //
    pixy.ccc.getBlocks();
    //The returned blocks are sorted by area, with the largest blocks appearing first in the blocks array.
    
    // Were blocks detected? //
    if (pixy.ccc.numBlocks)
    {
        for (block_index = 0; block_index < pixy.ccc.numBlocks; ++block_index)
        {
            if(pixy.ccc.blocks[block_index].m_signature == FOOD)
            {
                auto food = make_pair(pixy.ccc.blocks[block_index].m_width*pixy.ccc.blocks[block_index].m_height, pixy.ccc.blocks[block_index].m_x);
                foodQ.push(food);
            }
            else if(pixy.ccc.blocks[block_index].m_signature == TOXIC)
            {
                auto toxic = make_pair(pixy.ccc.blocks[block_index].m_width*pixy.ccc.blocks[block_index].m_height, pixy.ccc.blocks[block_index].m_x);
                toxicQ.push(toxic);
            }
            else
            {
                continue;
            }
        }
    }
}

array<Obj, 2> PixyCam::pickLarge()
{
    array<Obj, 2> tmp;

    if(!foodQ.empty())
    {
        tmp[0] = foodQ.front();
    }
    else
    {
        tmp[0] = make_pair(0, 0);
    }

    if(!toxicQ.empty())
    {
        tmp[1] = toxicQ.front();
    }
    else
    {
        tmp[1] = make_pair(0, 0);
    }

    return tmp;
}

PixyCam::~PixyCam()
{
    while(!foodQ.empty())
    {
        foodQ.pop();
    }
    while(!toxicQ.empty())
    {
        toxicQ.pop();
    }
}
