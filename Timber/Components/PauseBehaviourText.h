#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Render;
}

namespace timber
{
    // todo: what is this name?
    class PauseBehaviourText final : public diji::Component
    {
    public:
        explicit PauseBehaviourText(diji::GameObject* ownerPtr);
        ~PauseBehaviourText() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void OnGameOver();
        void Reset();
        void RefreshDisplay();

    private:
        diji::Render* m_RenderCompPtr;
        bool m_IsPaused = false;
    };
}

