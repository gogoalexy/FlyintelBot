#ifndef TIMER_H

#include <chrono>

using steadyClock = std::chrono::steady_clock;

//std::chrono::system_clock::time_point m_start;

inline void timerToZero(steadyClock::time_point &m_start)
{
    m_start = steadyClock::time_point::min();
};

inline void timerStart(steadyClock::time_point &m_start)
{
    m_start = steadyClock::now();
};

inline unsigned long timerGetMillis(steadyClock::time_point &m_start)
{
    steadyClock::duration diff;
    diff = steadyClock::now() - m_start;
    return (unsigned)(std::chrono::duration_cast<std::chrono::milliseconds>(diff).count());
};

#define TIMER_H
#endif
