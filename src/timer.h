#ifndef TIMER_H

#include <chrono>
#include <ctime>
#include <string>

using steadyClock = std::chrono::steady_clock;

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

inline std::string getDateTime()
{
    char time[10]
    auto now = std::time(nullptr);
    auto t = std::localtime(&now);
    std::strftime(time, 50, "%m%d-%H%M", t);
    std::string ret(time);
    return ret;
};

#define TIMER_H
#endif
