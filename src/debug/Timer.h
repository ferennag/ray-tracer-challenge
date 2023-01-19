#ifndef RAY_TRACER_CHALLENGE_TIMER_H
#define RAY_TRACER_CHALLENGE_TIMER_H

#include <string_view>
#include <SDL.h>

class Timer {
public:
    Timer();

    Uint64 elapsedMs();
    Uint64 totalMs() const;

    void restart();
    void reportElapsed(std::string_view text);
private:
    Uint64 m_start;
    Uint64 m_lastCheck;
};


#endif //RAY_TRACER_CHALLENGE_TIMER_H
