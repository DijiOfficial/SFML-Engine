#pragma once
#include "Engine/Components/Component.h"
#include <SFML/System/Vector2.hpp>

namespace diji
{
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

        // getpos
        // getShape?
        // GetVelocity
        // 
    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        bool m_DirtyFlagUpdate = false;
        int m_Size = 0;
        
        float m_Speed = 3000.0f;
        sf::Vector2f m_Velocity = { 0.2f, 0.2f };
    };
}
