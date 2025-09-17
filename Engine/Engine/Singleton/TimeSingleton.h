#pragma once
#include "Singleton.h"

namespace diji
{
    class TimeSingleton final : public Singleton<TimeSingleton>
    {
    public:
        [[nodiscard]] float GetDeltaTime() const { return m_DeltaTime; }
        void SetDeltaTime(const float deltaTime) { m_DeltaTime = deltaTime; }

        [[nodiscard]] float GetFixedUpdateDeltaTime() const { return m_FixedTimeStep; }
        void SetFixedUpdateDeltaTime(const float fixedTimeStep) { m_FixedTimeStep = fixedTimeStep; }

    private:
        float m_DeltaTime = 0.0f;
        float m_FixedTimeStep = .0f;
    };
}