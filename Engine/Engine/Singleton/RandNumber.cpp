#include "RandNumber.h"

#include <random>

int diji::RandNumber::GetRandomRangeInt(const int min, const int max) const
{
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

float diji::RandNumber::GetRandomRangeFloat(const float min, const float max) const
{
    static thread_local std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(rng);
}

