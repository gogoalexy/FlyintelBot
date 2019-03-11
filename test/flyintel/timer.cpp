#include "timer.h"

using namespace std::chrono;

Timer::Timer() : m_start(steady_clock::time_point::zero())
{}

void Timer::toZero()
{
    m_start = steady_clock::time_point::zero();
}

void Timer::start()
{
    m_start = steady_clock::now();
}

bool isStarted()
{
    return (m_start.time_since_epoch() != steady_clock::duration(0));
}

unsigned long getMillis()
{
    if(isStarted())
    {
        steady_clock::duration diff;
        diff = steady_clock::now() - m_start;
        return (unsigned)(duration_cast<milliseconds>(diff).count());
    }
    return 0;
}
