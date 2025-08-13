#include "PickUpBase.h"

#include "Player.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"

zombieArena::PickUpBase::PickUpBase(diji::GameObject* ownerPtr, const sf::IntRect& arena)
    : Component(ownerPtr)
    , m_Arena{ arena }
{
    m_Arena = sf::IntRect{ arena.position + sf::Vector2i{ 25, 25 }, arena.size + sf::Vector2i{ 25, 25 } };    
}

void zombieArena::PickUpBase::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();
    
    Spawn();
}

void zombieArena::PickUpBase::FixedUpdate()
{
    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr);
    for (const auto& collider : colliders)
    {
        if (!collider->GetParent()->HasComponent<Player>())
            continue;

        PickedUp(collider->GetParent());
        diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
        break;
    }
}

void zombieArena::PickUpBase::Spawn() const
{
    const int randomX = diji::RandNumber::GetRandomRangeInt(m_Arena.position.x, m_Arena.size.x);
    const int randomY = diji::RandNumber::GetRandomRangeInt(m_Arena.position.y, m_Arena.size.y);

    m_TransformCompPtr->SetPosition(static_cast<float>(randomX), static_cast<float>(randomY));

    // (void)diji::TimerManager::GetInstance().SetTimer([&]()
    // {
    //     diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
    // }, LIFETIME, false);
}


