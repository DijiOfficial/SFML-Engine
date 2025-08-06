#pragma once
#include <SFML/Graphics/Rect.hpp>

#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
    class TextureComp;
}

namespace zombieArena
{
    class Player final : public diji::Component
    {
    public:
        explicit Player(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Player() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void Spawn(const sf::IntRect& arena, const int tileSize);
        void ResetStats();
        bool Hit(const int damage);
        sf::Vector2f GetDirection() const { return m_Direction; }
        void SetDirection(const sf::Vector2f& direction) { m_Direction = direction; }
        // double GetLastHitTime() const { return m_LastHitTime; }
        // GetPosition() const { return m_TransformCompPtr->GetPosition(); }
        // GetCenter();

        void UpgradeSpeed() { m_CurrentSpeed += START_SPEED * 0.2f; }
        void UpgradeHealth();
        void Heal(const int amount);
        // int GetCurrentHealth() const { return m_CurrentHealth; }
        void OrientPlayer(const sf::Vector2i& mousePos);
        void PauseGame();

        diji::Event<> OnPauseEvent;

    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::TextureComp* m_TextureCompPtr = nullptr;
        sf::IntRect m_Arena = {};
        sf::Vector2f m_Direction = {0, 0};
        sf::Vector2i m_LastMousePos = {0, 0};
        
        const int START_HEALTH = 100;
        int m_CurrentHealth = START_HEALTH;
        int m_MaxHealth = START_HEALTH;
        int m_TileSize = 0;
        const float START_SPEED = 200.0f;
        float m_CurrentSpeed = START_SPEED;
        const float INVINCIBILITY_TIME = 0.2f;
        bool m_IsHit = false;
    };
}
