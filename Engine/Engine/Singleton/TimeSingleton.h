#pragma once
#include "Singleton.h"

namespace diji
{
    class TimeSingleton final : public Singleton<TimeSingleton>
    {
    public:
        float GetDeltaTime() const { return m_DeltaTime; }
        void SetDeltaTime(const float deltaTime) { m_DeltaTime = deltaTime; }

    private:
        float m_DeltaTime = 0.0f;
    };
}