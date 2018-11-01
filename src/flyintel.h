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
char motorNeuron();
void refresh();

private:
Container motor;
Ratio decision;
int spiketrain[300];

};

#define FLYINTEL_H
#endif
