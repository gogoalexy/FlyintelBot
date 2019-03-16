/*
 *    This file is part of FlyintelBot.
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

#include "HC_SR04.h"

HCSR04::HCSR04() : TrigPin(0), EchoPin(1), TimeOut(10000)
{
    std::cout<<"Warning: Parameters undefined! Default: Trig=0, Ech0=1, TimeOut=10000"<<endl;
}

HCSR04::HCSR04(short trigPin, short echoPin, int timeout)
 : TrigPin(trigPin), EchoPin(echoPin), TimeOut(timeout)
{
    travelTime = 0;
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    digitalWrite(TrigPin, LOW);
}

void HCSR04::init()
{
    pinMode(TrigPin, OUTPUT);
    pinMode(EchoPin, INPUT);
    digitalWrite(TrigPin, LOW);
}

unsigned int HCSR04::range()
{
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

unsigned int HCSR04::UsoundRange()
{
    travelTime = 0;
    digitalWrite(TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(TrigPin, LOW);
    unsigned long currtime = micros();
    while(digitalRead(EchoPin) == LOW)
    {
        if((micros() - currtime) > timeout)
        {
            return timeout;
        }
    }
    unsigned long start = micros();
    while(travelTime < timeout)
    {
        travelTime = micros() - start;
        if(digitalRead(EchoPin) == LOW)
        {
            break;
        }
    }
    return travelTime;
}
