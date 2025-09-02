#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class RectRender;
}

namespace zombieArena
{
    class HealthBar final : public diji::Component
    {
    public:
        explicit HealthBar(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~HealthBar() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void UpdateHealthBar(int health) const;
    private:
        diji::RectRender* m_RectRenderCompPtr = nullptr;
        const float HEALTH_BAR_HEIGHT = 50.f;
    };
}
