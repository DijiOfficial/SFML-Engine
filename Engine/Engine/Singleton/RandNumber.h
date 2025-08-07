#pragma once
#include <random>

namespace diji
{
    class RandNumber
    {
    public:
        static int GetRandomRangeInt(const int min, const int max)
        {
            static thread_local std::mt19937 rng(std::random_device{}());
            std::uniform_int_distribution<int> dist(min, max);
            return dist(rng);
        }

        static float GetRandomRangeFloat(const float min, const float max)
        {
            static thread_local std::mt19937 rng(std::random_device{}());
            std::uniform_real_distribution<float> dist(min, max);
            return dist(rng);
        }
    };
}
