#pragma once
#include "Engine/Components/ScoreCounter.h"

namespace zombieArena
{
    class HighScore final : public diji::ScoreCounter
    {
    public:
        using ScoreCounter::ScoreCounter;
        ~HighScore() noexcept override = default;

        void Init() override;

        void SaveHighScore() const;
        void UpdateScore(int value);
    };
}
