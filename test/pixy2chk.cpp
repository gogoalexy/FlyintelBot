#include <iostream>
#include <array>
#include <cmath>
#include "../src/pixycam.h"

#define CENTER_X 154
#define LEFT_X 0
#define RIGHT_X 319

using namespace std;

int main(){
	int frame = 0;
	PixyCam pixy;
	pixy.vision_init();

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
		float sensor = retina[0].first;

		cout<<center<<", "<<sensor<<", "<<endl;
		pixy.refresh();

	}
}
