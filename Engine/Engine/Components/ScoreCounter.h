#pragma once
#include <string>

#include "Component.h"

namespace diji
{
    class TextComp;

    class ScoreCounter final : public Component
    {
    public:
        explicit ScoreCounter(GameObject* ownerPtr, int score = 0);
        ~ScoreCounter() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}
        
        void IncreaseScore([[maybe_unused]] bool isLeft = false);
        [[nodiscard]] int GetScore() const { return m_Score; }
        void SetString(const std::string& str) { m_StringScore = str; }
        void Reset();

        Event<int> OnScoreIncreasedEvent;

    private:
        int m_Score;
        std::string m_StringScore = "Score = ";
        
        TextComp* m_TextCompPtr;
    };
}

