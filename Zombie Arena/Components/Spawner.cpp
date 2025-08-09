#include "Spawner.h"

#include "Zombie.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"

void zombieArena::Spawner::Init()
{
    m_ZombieTemplatePtr = std::make_unique<diji::GameObject>();
    m_ZombieTemplatePtr->AddComponents<diji::Transform>(500, 500);
    m_ZombieTemplatePtr->AddComponents<diji::TextureComp>();
    m_ZombieTemplatePtr->AddComponents<diji::Render>();
    m_ZombieTemplatePtr->AddComponents<Zombie>(diji::SceneManager::GetInstance().GetGameObject("X_Player"), ZombieType::BLOATER);

    (void)diji::TimerManager::GetInstance().SetTimer([&, this]()
    {
        diji::SceneManager::GetInstance().SpawnGameObject("W_Zombie", m_ZombieTemplatePtr.get(), sf::Vector2f{ 100, 100 });
    }, 1.0f, true);
}

void zombieArena::Spawner::Update()
{
    
}
