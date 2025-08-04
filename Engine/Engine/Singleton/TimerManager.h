#pragma once
#include "Singleton.h"

#include <functional>

namespace diji
{
    class TimeSingleton;
}

class TimerManager final : public diji::Singleton<TimerManager>
{
public:
    void Init();
    void Update();

    // Timer handle (for canceling or checking)
    struct TimerHandle
    {
        size_t id = 0;
    };

    // todo: Use template for better and cleaner code, make use create a TimerHandle and pass it instead of returning one.
    [[nodiscard]] TimerHandle SetTimer(std::function<void()> callback, float interval, bool isLooping = false, float initialDelay = 0.0f);
    void ClearTimer(const TimerHandle& handle);

private:
    diji::TimeSingleton* m_TimeSingleton = nullptr;
    struct Timer
    {
        size_t id;
        std::function<void()> callback;
        float timeRemaining;
        float interval;
        bool looping;
    };

    std::vector<Timer> m_Timers;
    size_t m_NextId = 1;
};
