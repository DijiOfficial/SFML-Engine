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
    m_InnerArenaRect = sf::IntRect{ sf::Vector2i{ 50, 50 }, sf::Vector2i{ 2000 - 100, 1100 - 100 } };
    if (!m_HealthPickUpTemplate)
    {
        m_HealthPickUpTemplate = std::make_unique<diji::GameObject>();
        m_HealthPickUpTemplate->AddComponents<diji::Transform>(0, 0);
        m_HealthPickUpTemplate->AddComponents<diji::TextureComp>();
        m_HealthPickUpTemplate->GetComponent<diji::TextureComp>()->SetOriginToCenter();
        m_HealthPickUpTemplate->AddComponents<diji::Render>();
        m_HealthPickUpTemplate->AddComponents<diji::Collider>();
        m_HealthPickUpTemplate->AddComponents<PickUpBase>(m_InnerArenaRect, "graphics/health_pickup.png", PickUpType::HEALTH, 50);
    }

    if (!m_AmmoPickUpTemplate)
    {
        m_AmmoPickUpTemplate = std::make_unique<diji::GameObject>();
        m_AmmoPickUpTemplate->AddComponents<diji::Transform>(0, 0);
        m_AmmoPickUpTemplate->AddComponents<diji::TextureComp>();
        m_AmmoPickUpTemplate->GetComponent<diji::TextureComp>()->SetOriginToCenter();
        m_AmmoPickUpTemplate->AddComponents<diji::Render>();
        m_AmmoPickUpTemplate->AddComponents<diji::Collider>();
        m_AmmoPickUpTemplate->AddComponents<PickUpBase>(m_InnerArenaRect, "graphics/ammo_pickup.png", PickUpType::AMMO, 12);
    }
    diji::SceneManager::GetInstance().SpawnGameObject("D_AmmoPickup", m_AmmoPickUpTemplate.get(), sf::Vector2f{ 0, 0 });
    diji::SceneManager::GetInstance().SpawnGameObject("D_HealthPickup", m_HealthPickUpTemplate.get(), sf::Vector2f{ 0, 0 });

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

void zombieArena::GameManager::RespawnPickUp(const PickUpType type, int)
{
    float respawnTime = 0.f;
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


