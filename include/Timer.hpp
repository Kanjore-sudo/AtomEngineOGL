#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start;
public:
    Timer();
    void Reset();
    double GetElapsedSeconds();
    double GetElapsedMilliseconds();
};

#endif
