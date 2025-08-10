#pragma once
#include "Engine/Components/Component.h"

#include <SFML/System/Vector2.hpp>

namespace diji
{
    class Transform;
    class Collider;
    class TextureComp;
}

namespace zombieArena
{
    class Bullet final : public diji::Component
    {
    public:
        explicit Bullet(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        explicit Bullet(diji::GameObject* ownerPtr, const sf::Vector2f& direction);
        ~Bullet() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void SetLifetime(const float lifetime) { m_Lifetime = lifetime; }
        void SetDirection(const sf::Vector2f& direction) { m_Direction = direction; }

    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::TextureComp* m_TextureCompPtr = nullptr;
        diji::Collider* m_ColliderCompPtr = nullptr;
        sf::Vector2f m_Direction = { 0.f, 0.f };
        const float m_Speed = 100.f;
        float m_Lifetime = 2.f;
    };
}
