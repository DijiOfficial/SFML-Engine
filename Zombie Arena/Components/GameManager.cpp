#include "GameManager.h"

#include "PickUpBase.h"
#include "../Core/GameState.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Singleton/TimerManager.h"

void zombieArena::GameManager::Init()
{
    m_InnerArenaRect = sf::IntRect{ sf::Vector2i{ 50, 50 }, GetMapSize() - sf::Vector2i{ 100, 100 } };
    if (!m_HealthPickUpTemplate)
    {
        m_HealthPickUpTemplate = std::make_unique<diji::GameObject>();
        m_HealthPickUpTemplate->AddComponents<diji::Transform>(0, 0);
        m_HealthPickUpTemplate->AddComponents<diji::TextureComp>();
        m_HealthPickUpTemplate->GetComponent<diji::TextureComp>()->SetOriginToCenter();
        m_HealthPickUpTemplate->AddComponents<diji::Render>();
        m_HealthPickUpTemplate->AddComponents<diji::Collider>();
        m_HealthPickUpTemplate->AddComponents<PickUpBase>(m_InnerArenaRect, "graphics/health_pickup.png", PickUpType::HEALTH, m_HealthReceivedOnPickUp);
    }

    if (!m_AmmoPickUpTemplate)
    {
        m_AmmoPickUpTemplate = std::make_unique<diji::GameObject>();
        m_AmmoPickUpTemplate->AddComponents<diji::Transform>(0, 0);
        m_AmmoPickUpTemplate->AddComponents<diji::TextureComp>();
        m_AmmoPickUpTemplate->GetComponent<diji::TextureComp>()->SetOriginToCenter();
        m_AmmoPickUpTemplate->AddComponents<diji::Render>();
        m_AmmoPickUpTemplate->AddComponents<diji::Collider>();
        m_AmmoPickUpTemplate->AddComponents<PickUpBase>(m_InnerArenaRect, "graphics/ammo_pickup.png", PickUpType::AMMO, m_AmmoReceivedOnPickUp);
    }
    const auto ammo = diji::SceneManager::GetInstance().SpawnGameObject("D_AmmoPickup", m_AmmoPickUpTemplate.get(), sf::Vector2f{ 0, 0 });
    const auto health = diji::SceneManager::GetInstance().SpawnGameObject("D_HealthPickup", m_HealthPickUpTemplate.get(), sf::Vector2f{ 0, 0 });

    ammo->GetComponent<PickUpBase>()->SetValue(m_AmmoReceivedOnPickUp);
    health->GetComponent<PickUpBase>()->SetValue(m_HealthReceivedOnPickUp);
    OnPickedUpEvent.AddListener(this, &GameManager::RespawnPickUp);
}

void zombieArena::GameManager::IncrementCurrentWave()
{
    ++m_CurrentWave;

    diji::TimerManager::GetInstance().ClearTimer(m_AmmoRespawnTimerHandle);
    diji::TimerManager::GetInstance().ClearTimer(m_HealthRespawnTimerHandle);
    OnZombieKilledEvent.ClearListeners();
    OnPickedUpEvent.ClearListeners();
    diji::SceneManager::GetInstance().SetNextSceneToActivate(static_cast<int>(ZombieGameState::Upgrading));
}

void zombieArena::GameManager::Upgrade(const UpgradeType upgrade)
{
    switch (upgrade)
    {
    case UpgradeType::FIRE_RATE:
        ++m_PlayerFireRate;
        break;
    case UpgradeType::CLIP_SIZE:
        m_MaxClipSize += m_MaxClipSize;
        break;
    case UpgradeType::HEALTH:
        m_MaxHealth += 20;
        break;
    case UpgradeType::SPEED:
        m_RunSpeed += 40;
        break;
    case UpgradeType::HEALTH_PICKUP:
        m_HealthReceivedOnPickUp += 25;
        m_HealthTimerRespawn -= 1.f;
        break;
    case UpgradeType::AMMO_PICKUP:
        m_AmmoReceivedOnPickUp += 6;
        m_AmmoTimerRespawn -= 1.f;
        break;
    case UpgradeType::TOTAL_TYPES:
    default:
        break;
    }
}

void zombieArena::GameManager::RespawnPickUp(const PickUpType type, int)
{
    float respawnTime;
    switch (type)
    {
    case PickUpType::HEALTH:
        respawnTime = m_HealthTimerRespawn;
        m_HealthRespawnTimerHandle = diji::TimerManager::GetInstance().SetTimer([&, this]()
        {
            diji::SceneManager::GetInstance().SpawnGameObject("D_HealthPickup", m_HealthPickUpTemplate.get(), sf::Vector2f{ 0, 0 });
        }, respawnTime, false);
        break;
    case PickUpType::AMMO:
        respawnTime = m_AmmoTimerRespawn;
        m_AmmoRespawnTimerHandle = diji::TimerManager::GetInstance().SetTimer([&, this]()
        {
            diji::SceneManager::GetInstance().SpawnGameObject("D_AmmoPickup", m_AmmoPickUpTemplate.get(), sf::Vector2f{ 0, 0 });
        }, respawnTime, false);
        break;
    case PickUpType::NONE:
    default:
        break;
    }
}

void zombieArena::GameManager::Reset()
{
    // yeah I could use named variables or even better load them from a file
    m_CurrentWave = 1;
    m_CurrentPlayerScore = 0;
    m_CurrentPlayerTotalBullets = 24;
    m_CurrentPlayerBulletsInClip = 6;
    m_PlayerFireRate = 1.f;
    m_MaxClipSize = 6;
    m_MaxHealth = 100;
    m_CurrentPlayerHealth = 100;
    m_RunSpeed = 200.f;
    m_HealthReceivedOnPickUp = 50;
    m_AmmoReceivedOnPickUp = 12;
    m_AmmoTimerRespawn = 10.f;
    m_HealthTimerRespawn = 10.f;

    diji::TimerManager::GetInstance().ClearTimer(m_AmmoRespawnTimerHandle);
    diji::TimerManager::GetInstance().ClearTimer(m_HealthRespawnTimerHandle);
    OnZombieKilledEvent.ClearListeners();
    OnPickedUpEvent.ClearListeners();
    diji::SceneManager::GetInstance().SetNextSceneToActivate(static_cast<int>(ZombieGameState::StartMenu));
}
