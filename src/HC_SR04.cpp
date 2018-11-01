#include "HC_SR04.h"


HCSR04::HCSR04(short TrigPin = 0, short EchoPin = 1, int TimeOut = 10000){
	this->TrigPin = TrigPin;
	this->EchoPin = EchoPin;
	this->timeout = TimeOut;
	travelTime = 0;
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
	digitalWrite(TrigPin, LOW);
}

unsigned long HCSR04::UsoundRange(){
    travelTime = 0;
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	unsigned long currtime = micros();
	while(digitalRead(EchoPin) == LOW){
		if((micros() - currtime) > timeout){
			return timeout;
		}
	}
	unsigned long start = micros();
	while(travelTime < timeout){
		travelTime = micros() - start;
		if(digitalRead(EchoPin) == LOW){
			break;
		}
	}
	return travelTime;
}
