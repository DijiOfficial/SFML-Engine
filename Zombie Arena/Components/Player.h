#pragma once
#include "Engine/Components/Component.h"

#include <SFML/Graphics/Rect.hpp>

namespace diji
{
    class Camera;
    class Transform;
    class TextureComp;
}

namespace zombieArena
{
    class Pistol;

    class Player final : public diji::Component
    {
    public:
        explicit Player(diji::GameObject* ownerPtr, const sf::IntRect& arena);
        ~Player() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void Spawn(const sf::IntRect& arena, int tileSize);
        void ResetStats();
        bool Hit(int damage);
        sf::Vector2f GetDirection() const { return m_Direction; }
        void SetDirection(const sf::Vector2f& direction) { m_Direction = direction; }

        void UpgradeSpeed() { m_CurrentSpeed += START_SPEED * 0.2f; }
        void UpgradeHealth();
        void Heal(int amount);
        void OrientPlayer(const sf::Vector2i& mousePos);
        void PauseGame();
        
        void GivePistol(const diji::GameObject* object);  
        void Shoot(bool isStart) const;

        diji::Event<> OnPauseEvent;

    private:
        diji::Camera* m_CameraCompPtr = nullptr;
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::TextureComp* m_TextureCompPtr = nullptr;
        Pistol* m_PistolCompPtr = nullptr;
        sf::IntRect m_Arena;
        sf::Vector2f m_Direction = {0, 0};
        sf::Vector2f m_LookingDirection = {0, 0};
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
