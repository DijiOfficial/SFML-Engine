#pragma once
#include "Engine/Components/ScoreCounter.h"

namespace zombieArena
{
    class CustomScoreCounter final : public diji::ScoreCounter
    {
    public:
        using ScoreCounter::ScoreCounter;
        ~CustomScoreCounter() noexcept override = default;

        void Start() override;
        void SaveScore();

        diji::Event<int> OnScoreSetEvent;
    };
}
