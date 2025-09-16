#pragma once
#include "Engine/Components/Component.h"

#include <SFML/Graphics/Rect.hpp>

#include "Engine/Singleton/TimerManager.h"

namespace zombieArena
{
    enum class PickUpType;
}

namespace diji
{
    class Collider;
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
        void Start() override;
        
        void Update() override;
        void FixedUpdate() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override;

        void Spawn(const sf::IntRect& arena, int tileSize);
        bool Hit(int damage);
        [[nodiscard]] sf::Vector2f GetDirection() const { return m_Direction; }
        void SetDirection(const sf::Vector2f& direction) { m_Direction = direction; }

        void HandlePickups(PickUpType, int value);
        void OrientPlayer(const sf::Vector2i& mousePos);
        void PauseGame();
        
        void GivePistol(const diji::GameObject* object);  
        void Shoot(bool isStart) const;
        void Reload() const;
        
        diji::Event<> OnPauseEvent;
        diji::Event<> OnDeathEvent;
        diji::Event<int> OnHealthChangeEvent;

    private:
        diji::Camera* m_CameraCompPtr = nullptr;
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::TextureComp* m_TextureCompPtr = nullptr;
        diji::Collider* m_ColliderCompPtr = nullptr;
        Pistol* m_PistolCompPtr = nullptr;
        diji::TimerManager::TimerHandle m_InvincibilityTimerHandle;
        sf::IntRect m_Arena;
        sf::Vector2f m_Direction = {0, 0};
        sf::Vector2f m_LookingDirection = {0, 0};
        sf::Vector2i m_LastMousePos = {0, 0};
        
        int m_CurrentHealth = 100;
        int m_MaxHealth = 100;
        int m_TileSize = 0;
        // const float START_SPEED = 200.0f;
        float m_CurrentSpeed = 200.f;
        const float INVINCIBILITY_TIME = 0.2f;
        bool m_IsHit = false;

        void Heal(int amount);
        void GiveAmmo(int value) const;
    };
}
