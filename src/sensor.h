#ifndef SENSOR_H

#include <iostream>

class Sensor {
public:
virtual void init() {
    std::cout<<"no sensor specified"<<endl;
    return;
}
virtual unsigned int range() {
    std::cout<<"no sensor specified"<<endl;
    return 100;
}

};

#define SENSOR_H
#endif
