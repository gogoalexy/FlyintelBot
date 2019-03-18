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

#include "flyintel.h"

using namespace std;

Flyintel::Flyintel(): count{0}, decision{0.0}
{}

void Flyintel::sortingHat(const SpikesHandler &spikesData)
{
    for(int i=2; i<spikesData.maxDataBytes; i+=3)
    {
        switch(spikesData.spiketrain[i])
        {
            case 56:
                count.forward++;
                break;
            case 62:
                count.backward++;
                break;
            case 68:
                count.left++;
                break;
            case 74:
                count.right++;
                break;
            default:
                ;
        }
    }
}

motor Flyintel::getMotor()
{
    decision.denom = count.forward+count.backward+count.right+count.left;
    if(decision.denom == 0)
        decision.denom = 1;
    if(decision.denom)
    {
        decision.rforward = count.forward/decision.denom;
        decision.rbackward = count.backward/decision.denom;
        decision.rleft = count.left/decision.denom;
        decision.rright = count.right/decision.denom;
        cout<<decision.rforward<<";";
        cout<<decision.rbackward<<";";
        cout<<decision.rleft<<";";
        cout<<decision.rright<<";"<<endl;
    }

    if(decision.rforward<=0.5 && decision.rbackward<=0.5 && decision.rleft<=0.5 && decision.rright<=0.5)
    {
        return make_pair(0x0, 0); //S
    }
    else if(decision.rforward>0.5)
    {
        return make_pair(0x1, short(1024*decision.rforward)); //F
    }
    else if(decision.rbackward>0.5)
    {
        return make_pair(0x2, short(1024*decision.rbackward)); //B
    }
    else if(decision.rleft>0.5)
    {
        return make_pair(0x4, short(1024*decision.rleft)); //L
    }
    else if(decision.rright>0.5)
    {
        return make_pair(0x8, short(1024*decision.rright)); //R
    }
    else
    {
        return make_pair(0x0, 0); //S
    }
}

void Flyintel::clear()
{
    count.forward=0;
    count.backward=0;
    count.left=0;
    count.right=0;
}
