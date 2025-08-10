#include "Bullet.h"

#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Collision/Collider.h"

zombieArena::Bullet::Bullet(diji::GameObject* ownerPtr, const sf::Vector2f& direction)
    : Component(ownerPtr)
    , m_Direction{ direction }
{
}

void zombieArena::Bullet::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();

    (void)diji::TimerManager::GetInstance().SetTimer([&]()
    {
        diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
    }, m_Lifetime, false);
}

void zombieArena::Bullet::Update()
{
    // todo: optimize the calls to CollisionSingleton and TimeSingleton
    const auto deltaMovement = m_Direction * m_Speed * diji::TimeSingleton::GetInstance().GetDeltaTime();
    m_TransformCompPtr->AddOffset(deltaMovement);
}
