#include <stdio.h>
#include "wiringPi.h"
#include "wiringPiSPI.h"
#include "mcp3004.h"

int main() {

wiringPiSetup();
mcp3004Setup(100, 0);

while(1){
    int val = analogRead(100);
    printf("%i.", val);

}

}
