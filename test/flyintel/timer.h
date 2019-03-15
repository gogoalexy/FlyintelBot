#ifndef TIMER_H

#include <chrono>

//auto system_clock::time_point m_start;

void timerToZero(auto &mstart)
{
    m_start = steady_clock::time_point::min();
}

inline void timerStart(auto &m_start)
{
    m_start = steady_clock::now();
}

inline unsigned long timerGetMillis(auto &m_start)
{
    system_clock::duration diff;
    diff = steady_clock::now() - m_start;
    return (unsigned)(duration_cast<milliseconds>(diff).count());
}

#define TIMER_H
#endif
