#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
}

namespace pong
{
    class Paddle final : public diji::Component
    {
    public:
        explicit Paddle(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Paddle() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void SetIsMovingLeft(const bool isMoving) { m_IsMovingLeft = isMoving; }
        void SetIsMovingRight(const bool isMoving) { m_IsMovingRight = isMoving; }

    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        float m_Speed = 1000.f;
        float m_SizeX = 0.f;
        const float m_LeftBound = 0.0f;
        float m_RightBound = 1920.0f; // todo: use the window singleton to get the width

        bool m_IsMovingLeft = false;
        bool m_IsMovingRight = false;
    };
}


