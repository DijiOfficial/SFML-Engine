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
        [[nodiscard]] float GetPlayerFireRate() const { return m_PlayerFireRate; }
        
        void IncrementCurrentWave();
        void SetCurrentPlayerScore(const int score) { m_CurrentPlayerScore = score; }
        void SetCurrentPlayerTotalBullets(const int totalBullets) { m_CurrentPlayerTotalBullets = totalBullets; }
        void SetCurrentPlayerBulletsInClip(const int bulletsInClip) { m_CurrentPlayerBulletsInClip = bulletsInClip; }
        void SetPlayerFireRate(const float fireRate) { m_PlayerFireRate = fireRate; }
        
    private:
        std::unique_ptr<diji::GameObject> m_AmmoPickUpTemplate = nullptr;
        std::unique_ptr<diji::GameObject> m_HealthPickUpTemplate = nullptr;
        sf::IntRect m_InnerArenaRect;
        diji::TimerManager::TimerHandle m_AmmoRespawnTimerHandle;
        diji::TimerManager::TimerHandle m_HealthRespawnTimerHandle;

        int m_CurrentWave = 1;
        float m_AmmoTimerRespawn = 10.f;
        float m_HealthTimerRespawn = 10.f;
        int m_CurrentPlayerScore = 0;
        int m_CurrentPlayerTotalBullets = 24;
        int m_CurrentPlayerBulletsInClip = 6;
        float m_PlayerFireRate = 1.f;

        void RespawnPickUp(PickUpType type, int);
    };
}
