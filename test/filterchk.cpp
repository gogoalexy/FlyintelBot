#include <iostream>
#include <array>
#include <utility>
#include "../src/sensefilter.h"

#define CENTER_X 154
#define LEFT_X 0
#define RIGHT_X 319

using namespace std;

typedef std::pair<int, int> obj;

int main(){
	int frame = 0;
	int x, area;

	LinearFilter lfc(CENTER_X, 1, 100);
	LinearFilter lfl(LEFT_X, 1, 60);
	LinearFilter lfr(RIGHT_X, 1, 60);

	while(true){
		frame += 1;
		array<obj, 2> retina;
		cin>>x>>area;
		retina[0].first = area;
		retina[0].second = x;
		cout<<"frame: "<<frame<<endl;

		float x = retina[0].second;
		float area = retina[0].first;
		if(area > 6000){
			area = 6000;
		}

		float objC = lfc.FilterGen(x)*area;
		float objL = lfl.FilterGen(x)*area;
		float objR = lfr.FilterGen(x)*area;

		cout<<objC<<", "<<objL<<", "<<objR<<", "<<endl;

	}
}
