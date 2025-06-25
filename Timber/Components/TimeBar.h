#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class RectRender;
}

namespace timber 
{
    class TimeBar final : public diji::Component
    {
    public:
        explicit TimeBar(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~TimeBar() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
		
        void FixedUpdate() override {}
        void Update() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        diji::Event<> OnGameOverEvent;

        void Reset();
        void AddTime(int score);
        
    private:
        diji::RectRender* m_RectRenderCompPtr = nullptr;
        float m_RemainingTime = 6.f;
        float m_WidthPerSecond = 200.f / 6.f; // I could use values from the RenderRect instead of magic numbers
    };
}
