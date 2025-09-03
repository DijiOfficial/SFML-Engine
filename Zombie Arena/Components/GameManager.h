#pragma once
#include <memory>
#include <SFML/Graphics/Rect.hpp>

#include "Engine/Singleton/Singleton.h"
#include "Engine/Interfaces/EventSystem.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimerManager.h"

//todo: add zombie counter and scene changes
// todo: increase core when zombie dies
namespace zombieArena
{
    enum class PickUpType;
    enum class UpgradeType
    {
        FIRE_RATE,
        CLIP_SIZE,
        HEALTH,
        SPEED,
        HEALTH_PICKUP,
        AMMO_PICKUP,
        TOTAL_TYPES
    };
    
    class GameManager final : public diji::Singleton<GameManager>
    {
    public:
        void Init();
        diji::Event<PickUpType, int> OnPickedUpEvent;
        diji::Event<> OnZombieKilledEvent;

        [[nodiscard]] int GetCurrentWave() const { return m_CurrentWave; }
        [[nodiscard]] int GetCurrentPlayerScore() const { return m_CurrentPlayerScore; }
        [[nodiscard]] int GetCurrentPlayerTotalBullets() const { return m_CurrentPlayerTotalBullets; }
        [[nodiscard]] int GetCurrentPlayerBulletsInClip() const { return m_CurrentPlayerBulletsInClip; }
        [[nodiscard]] float GetPlayerFireRate() const { return 1 / m_PlayerFireRate; }
        [[nodiscard]] int GetMaxClipSize() const { return m_MaxClipSize; }
        [[nodiscard]] int GetMaxHealth() const { return m_MaxHealth; }
        [[nodiscard]] float GetRunSpeed() const { return m_RunSpeed; }
        [[nodiscard]] int GetHealthReceivedOnPickUp() const { return m_HealthReceivedOnPickUp; }
        [[nodiscard]] int GetAmmoReceivedOnPickUp() const { return m_AmmoReceivedOnPickUp; }
        [[nodiscard]] int GetPlayerHealth() const { return m_CurrentPlayerHealth; }
        [[nodiscard]] sf::Vector2i GetMapSize() const { return sf::Vector2i{ 500 * m_CurrentWave,500 * m_CurrentWave }; }

        void IncrementCurrentWave();
        void SetCurrentPlayerScore(const int score) { m_CurrentPlayerScore = score; }
        void SetCurrentPlayerTotalBullets(const int totalBullets) { m_CurrentPlayerTotalBullets = totalBullets; }
        void SetCurrentPlayerBulletsInClip(const int bulletsInClip) { m_CurrentPlayerBulletsInClip = bulletsInClip; }

        void Upgrade(UpgradeType upgrade);
        void Reset();
        
    private:
        std::unique_ptr<diji::GameObject> m_AmmoPickUpTemplate = nullptr;
        std::unique_ptr<diji::GameObject> m_HealthPickUpTemplate = nullptr;
        sf::IntRect m_InnerArenaRect;
        diji::TimerManager::TimerHandle m_AmmoRespawnTimerHandle;
        diji::TimerManager::TimerHandle m_HealthRespawnTimerHandle;

        float m_AmmoTimerRespawn = 10.f;
        float m_HealthTimerRespawn = 10.f;
        float m_PlayerFireRate = 1.f;
        float m_RunSpeed = 200.f;
        int m_CurrentPlayerHealth = 100;
        int m_CurrentWave = 1;
        int m_CurrentPlayerScore = 0;
        int m_CurrentPlayerTotalBullets = 24;
        int m_CurrentPlayerBulletsInClip = 6;
        int m_MaxClipSize = 6;
        int m_MaxHealth = 100;
        int m_HealthReceivedOnPickUp = 50;
        int m_AmmoReceivedOnPickUp = 12;

        void RespawnPickUp(PickUpType type, int);
    };
}
