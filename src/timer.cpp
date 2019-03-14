#include "timer.h"

using namespace std::chrono;

Timer::Timer() : m_start(system_clock::time_point::min())
{}

void Timer::toZero()
{
    m_start = system_clock::time_point::min();
}

void Timer::start()
{
    m_start = system_clock::now();
}

bool isStarted()
{
    return (m_start.time_since_epoch() != system_clock::duration(0));
}

unsigned long getMillis()
{
    if(isStarted())
    {
        system_clock::duration diff;
        diff = system_clock::now() - m_start;
        return (unsigned)(duration_cast<milliseconds>(diff).count());
    }
    return 0;
}
