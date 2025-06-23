#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Render;
}

namespace timber
{
    class PauseBehaviourText final : public diji::Component
    {
    public:
        explicit PauseBehaviourText(diji::GameObject* ownerPtr);
        ~PauseBehaviourText() noexcept override = default;

        PauseBehaviourText(const PauseBehaviourText& other) = delete;
        PauseBehaviourText(PauseBehaviourText&& other) = delete;
        PauseBehaviourText& operator=(const PauseBehaviourText& other) = delete;
        PauseBehaviourText& operator=(PauseBehaviourText&& other) = delete;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void OnNotify(diji::MessageTypes message) override;
        
    private:
        diji::Render* m_RenderCompPtr;
        bool m_IsPaused = false;
    };
}

