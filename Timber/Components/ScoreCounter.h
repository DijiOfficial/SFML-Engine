#pragma once
// #include "Subject.h"
#include "Engine/Components/Component.h"

namespace timber
{
    // class ScoreCounter final : public diji::Component, public diji::Subject
    class ScoreCounter final : public diji::Component
    {
    public:
        explicit ScoreCounter(diji::GameObject* ownerPtr, int score);
        ~ScoreCounter() noexcept override = default;

        ScoreCounter(const ScoreCounter& other) = delete;
        ScoreCounter(ScoreCounter&& other) = delete;
        ScoreCounter& operator=(const ScoreCounter& other) = delete;
        ScoreCounter& operator=(ScoreCounter&& other) = delete;

        void Init() override {}
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}
        
        void IncreaseScore(int score);
        int GetScore() const { return m_Score; }

    private:
        int m_Score;
    };
}

