#include "sensefilter.h"

LinearFilter::LinearFilter(float mean, float max, float edgelen){
    this->mean = mean;
    this->max = max;
    this->edgelen = edgelen;
}

inline float LinearFilter::slope(){
	return ( this->max / this->edgelen );
}

float LinearFilter::FilterGen(int obj_x){
	return max - ( std::abs(obj_x - mean) * slope() );
}
