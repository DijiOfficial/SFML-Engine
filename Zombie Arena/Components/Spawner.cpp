#include "Spawner.h"

#include "GameManager.h"
#include "Zombie.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Singleton/RandNumber.h"

zombieArena::Spawner::Spawner(diji::GameObject* ownerPtr, diji::GameObject* playerPtr, const sf::IntRect& arena)
    : Component(ownerPtr)
    , m_PlayerPtr{ playerPtr }
    , m_Arena{ arena }
{
}

void zombieArena::Spawner::Init()
{
    m_ZombieTemplatePtr = std::make_unique<diji::GameObject>();
    m_ZombieTemplatePtr->AddComponents<diji::Transform>(500, 500);
    m_ZombieTemplatePtr->AddComponents<diji::TextureComp>();
    m_ZombieTemplatePtr->AddComponents<diji::Render>();
    m_ZombieTemplatePtr->AddComponents<diji::Collider>();
    m_ZombieTemplatePtr->AddComponents<Zombie>(m_PlayerPtr, ZombieType::BLOATER);

    // (void)diji::TimerManager::GetInstance().SetTimer([&, this]()
    // {
    //     diji::SceneManager::GetInstance().SpawnGameObject("W_Zombie", m_ZombieTemplatePtr.get(), sf::Vector2f{ 100, 100 });
    // }, 1.0f, true);
    (void)diji::TimerManager::GetInstance().SetTimer([&, this]()
    {
        const int totalZombiesSpawned = GameManager::GetInstance().GetCurrentWave() * ZOMBIE_PER_WAVE;
        CreateHorde(totalZombiesSpawned);
        OnWaveSpawnedEvent.Broadcast(totalZombiesSpawned);
    }, 0.1f, false);
}

void zombieArena::Spawner::CreateHorde(const int totalZombies) const
{
    constexpr int edgeOffset = 20;
    const float spawnMinX = static_cast<float>(m_Arena.position.x + edgeOffset);
    const float spawnMaxX = static_cast<float>(m_Arena.position.x + m_Arena.size.x - edgeOffset);
    const float spawnMinY = static_cast<float>(m_Arena.position.y + edgeOffset);
    const float spawnMaxY = static_cast<float>(m_Arena.position.y + m_Arena.size.y - edgeOffset);
    
    for (int i = 0; i < totalZombies; ++i)
    {
        const int edge = diji::RandNumber::GetRandomRangeInt(0, 3);
        sf::Vector2f spawnPos;

        switch (edge)
        {
        case 0: // Top edge
            spawnPos.x = diji::RandNumber::GetRandomRangeFloat(spawnMinX, spawnMaxX);
            spawnPos.y = static_cast<float>(m_Arena.position.y + edgeOffset);
            break;

        case 1: // Bottom edge
            spawnPos.x = diji::RandNumber::GetRandomRangeFloat(spawnMinX, spawnMaxX);
            spawnPos.y = static_cast<float>(m_Arena.position.y + m_Arena.size.y - edgeOffset);
            break;

        case 2: // Left edge
            spawnPos.x = static_cast<float>(m_Arena.position.x + edgeOffset);
            spawnPos.y = diji::RandNumber::GetRandomRangeFloat(spawnMinY, spawnMaxY);
            break;

        case 3: // Right edge
            spawnPos.x = static_cast<float>(m_Arena.position.x + m_Arena.size.x - edgeOffset);
            spawnPos.y = diji::RandNumber::GetRandomRangeFloat(spawnMinY, spawnMaxY);
            break;

        default:
            break;
        }
        
        const auto zombie = diji::SceneManager::GetInstance().SpawnGameObject("W_Zombie", m_ZombieTemplatePtr.get(), spawnPos);
        const auto zombieComp = zombie->GetComponent<Zombie>();

        const ZombieType type = static_cast<ZombieType>(diji::RandNumber::GetRandomRangeInt(0, static_cast<int>(ZombieType::TOTAL_ZOMBIE_TYPES) - 1));
        zombieComp->SetType(type);
    }
}

