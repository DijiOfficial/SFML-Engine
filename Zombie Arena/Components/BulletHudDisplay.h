#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class TextComp;
}

namespace zombieArena
{
    class BulletHudDisplay final : public diji::Component
    {
    public:
        explicit BulletHudDisplay(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~BulletHudDisplay() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void UpdateText(int currentAmmo, int maxAmmo) const;
        
    private:
        diji::TextComp* m_TextCompPtr = nullptr;
    };
}
