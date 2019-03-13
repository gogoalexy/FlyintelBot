#include "DCmotor.h"

using namespace std;

int main()
{
    wiringPiSetupGpio();
    
    DCmotor front(22, 23, 24, 25, 18, 12);
    DCmotor rear(4, 0, 1, 5, 13, 19);
    
    front.velocity(900, 900);
    rear.velocity(900, 900);
    
    front.left();
    delay(1000);
    rear.left();
    delay(1000);
    front.stop();
    rear.stop();

    return 0;
}
