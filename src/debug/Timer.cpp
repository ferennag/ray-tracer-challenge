#include <iostream>
#include "Timer.h"

Timer::Timer() {
    m_start = m_lastCheck = SDL_GetTicks64();
}

Uint64 Timer::elapsedMs() {
    auto now = SDL_GetTicks64();
    auto result = now - m_lastCheck;
    m_lastCheck = now;
    return result;
}

Uint64 Timer::totalMs() const {
    return SDL_GetTicks64() - m_start;
}

void Timer::restart() {
    m_start = m_lastCheck = SDL_GetTicks64();
}

void Timer::reportElapsed(std::string_view text) {
    auto elapsed = elapsedMs();
    std::cout << text << " [" << elapsed << " ms] " << std::endl;
}
