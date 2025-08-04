#pragma once
#include "Engine/Components/Component.h"
#include <SFML/System/Vector2.hpp>

namespace diji
{
    class CollisionSingleton;
}

namespace diji
{
    class Collider;
    class Transform;
    class ScoreCounter;
}

namespace pong
{
    class Ball final : public diji::Component
    {
    public:
        explicit Ball(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Ball() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void ResetBall();

        diji::Event<> OnLifeLostEvent;
        diji::Event<> OnIncreaseScoreEvent;
        
    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        bool m_DirtyFlagUpdate = false;
        bool m_DirtyFlagCollision = false;
        int m_Size = 0;

        diji::Collider* m_ColliderCompPtr = nullptr;
        diji::Collider* m_PaddleColliderCompPtr = nullptr; // todo: change collision system to decouple this.
        diji::CollisionSingleton* m_CollisionSingleton = nullptr;
        
        float m_Speed = 600.0f;
        float m_OriginalSpeed = 600.f;
        sf::Vector2f m_Velocity = { 0.2f, 0.2f };

        void CalculateNewVelocity();
    };
}
