#pragma once
#include "Engine/Components/ScoreCounter.h"

namespace zombieArena
{
    class WaveCounter final : public diji::ScoreCounter
    {
    public:
        using ScoreCounter::ScoreCounter;
        ~WaveCounter() noexcept override = default;

        void Init() override;
    };
}
