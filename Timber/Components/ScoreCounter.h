#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class TextComp;
}

namespace timber
{
    class ScoreCounter final : public diji::Component
    {
    public:
        explicit ScoreCounter(diji::GameObject* ownerPtr, int score = 0);
        ~ScoreCounter() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}
        
        void IncreaseScore(int score);
        [[nodiscard]] int GetScore() const { return m_Score; }

        void OnNotify(diji::MessageTypes message) override;

    private:
        int m_Score;
        diji::TextComp* m_TextCompPtr;
    };
}

