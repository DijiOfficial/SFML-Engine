#pragma once
#include <random>

namespace diji
{
    static thread_local std::mt19937 rng(std::random_device{}()); // cool thing I did not know, generating a device is slow and so only doing it once is good optimization

    class RandNumber final
    {
    public:
        static int GetRandomRangeInt(const int min, const int max)
        {
            std::uniform_int_distribution<int> dist(min, max);
            return dist(rng);
        }

        static float GetRandomRangeFloat(const float min, const float max)
        {
            std::uniform_real_distribution<float> dist(min, max);
            return dist(rng);
        }
    };
}
