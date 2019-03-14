#include "DCmotor.h"

using namespace std;

int main()
{
    wiringPiSetupGpio();
    
    DCmotor front(22, 23, 24, 25, 18, 12);
    DCmotor rear(4, 0, 1, 5, 13, 19);
    
    front.velocity(800, 800);
    rear.velocity(800, 800);
    
    front.left();
    delay(1000);
    rear.left();
    delay(1000);
    front.stop();
    rear.stop();

    return 0;
}
