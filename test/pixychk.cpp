#include <iostream>
#include <array>
#include <cmath>
#include "../src/attention.h"
#include "../src/sensefilter.h"

#define CENTER_X 154
#define LEFT_X 0
#define RIGHT_X 319

using namespace std;

int main(){
	int frame = 0;
	Attention pixy;
	LinearFilter lfc(CENTER_X, 1, 100);
	LinearFilter lfl(LEFT_X, 1, 60);
	LinearFilter lfr(RIGHT_X, 1, 60);

	while(true){
		frame += 1;
		pixy.capture();
		array<obj, 2> retina;
		retina = pixy.pick();
		cout<<"frame: "<<frame<<endl;

		float center = abs(retina[0].second - CENTER_X);
		if(!center){
			center = 1;
		}
		float sensor = retina[0].first/center;

		float objC = abs(lfc.FilterGen(center)*sensor);
		float objL = abs(lfl.FilterGen(center)*sensor);
		float objCR= abs(lfr.FilterGen(center)*sensor);

		cout<<objC<<", "<<objL<<", "<<objR<<", "<<endl;

	}
}
