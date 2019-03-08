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

#include "sensefilter.h"

LinearFilter::LinearFilter(float mean, float max, float edgelen){
    this->mean = mean;
    this->max = max;
    this->edgelen = edgelen;
}

inline float LinearFilter::slope(){
	return ( this->max / this->edgelen );
}

float LinearFilter::FilterGen(int objx){
	float dist_to_mean = std::abs(objx - mean);
	if(dist_to_mean > edgelen){
		return 0;
	}else{
		return max - ( dist_to_mean * slope() );
	}
}
