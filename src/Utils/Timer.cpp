#include "Timer.hpp"

Timer::Timer() { Reset(); }

void Timer::Reset() { start = std::chrono::high_resolution_clock::now(); }

double Timer::GetElapsedSeconds() {
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(now - start).count();
}

double Timer::GetElapsedMilliseconds() {
    return GetElapsedSeconds() * 1000.0;
}
