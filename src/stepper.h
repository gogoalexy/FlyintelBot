#ifndef STEPPER_H

#include <cmath>
#include <wiringPi.h>

class Stepper
{
public:
    Stepper(int number_of_steps, int pin1, int pin2, int pin3, int pin4); //bipolar 4-wire stepper
    void setSpeed(int rpm);
    void step(int do_steps);

protected:
    void stepMotor(int the_step);

private:
    const int STEPS;
    const int IN1;
    const int IN2;
    const int IN3;
    const int IN4;
    unsigned int step_interval;
    unsigned int last_step_time;
};

#define STEPPER_H
#endif
