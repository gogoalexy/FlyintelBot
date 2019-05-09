#include "stepper.h"

Stepper::Stepper(int number_of_steps, int pin1, int pin2, int pin3, int pin4) :
STEPS(number_of_steps), IN1(pin1), IN2(pin2), IN3(pin3), IN4(pin4)
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void Stepper::setSpeed(int rpm)
{
    step_interval = 60*1000*1000 / (rpm * STEPS);
}

void Stepper::step(int do_steps)
{
    int steps_left = std::abs(do_steps);

    while(steps_left)
    {
        unsigned int this_step_time = micros();
        unsigned int phase = 0;

        if(this_step_time - last_step_time >= step_interval)
        {
            last_step_time = this_step_time;
            if(do_steps > 0)
            {
                ++phase;
                if(phase == STEPS) {phase = 0;}
            }
            else
            {
                if(phase == 0) {phase = STEPS;}
                --phase;
            }
        }
        --steps_left;

        stepMotor(phase);
    }
}

void Stepper::stepMotor(int the_step)
{
    switch (the_step)
    {
      case 0:  // 1010
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      break;
      case 1:  // 0110
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      break;
      case 2:  //0101
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      break;
      case 3:  //1001
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      break;
    }
}
