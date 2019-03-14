#ifndef TIMER_H

#include <chrono>

class Timer
{
public:
    Timer();
    void toZero();
    void start();
    bool isStarted();
    unsigned long getMillis();

private:
    std::chrono::system_clock::time_point m_start;
};

#define TIMER_H
#endif
