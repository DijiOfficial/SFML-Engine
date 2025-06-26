#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Render;
    class Transform;
}

namespace timber
{
    class GravestoneBehaviour final : public diji::Component
    {
    public:
        explicit GravestoneBehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~GravestoneBehaviour() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void Move(bool isLeft = false);
        void Enable();
        void Reset();

    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::Render* m_RenderCompPtr = nullptr;

        float m_PosX = 0.f;
    };
}


