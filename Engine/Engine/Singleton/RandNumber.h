#pragma once
#include "Singleton.h"

namespace diji
{
    class RandNumber final : public Singleton<RandNumber>
    {
    public:
        int GetRandomRangeInt(int min, int max) const;
        float GetRandomRangeFloat(float min, float max) const;
    };
}