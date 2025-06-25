#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
}

namespace timber
{    
    class AxeBehaviour final : public diji::Component
    {
    public:
        explicit AxeBehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~AxeBehaviour() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void SetPosition(bool isLeft);
        void Reset();

    private:
        const float AXE_POSITION_LEFT = 700;
        const float AXE_POSITION_RIGHT = 1075;

        diji::Transform* m_Transform = nullptr;
    };
}


