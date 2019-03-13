#include "DCmotor.h"

using namespace std;

int main()
{
    wiringPiSetupGpio();
    
    DCmotor front(22, 23, 24, 25, 18, 12);
    DCmotor rear(4, 0, 1, 5, 13, 19);
    
    front.velocity(600, 600);
    rear.velocity(600, 600);
    
    front.forward();
    delay(1000);
    rear.backward();
    delay(1000);
    front.stop();
    rear.stop();

    return 0;
}
