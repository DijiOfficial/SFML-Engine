#include "Bullet.h"

#include "Zombie.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/TextureComp.h"

#include <numbers>

#include "GameManager.h"

zombieArena::Bullet::Bullet(diji::GameObject* ownerPtr, const sf::Vector2f& direction)
    : Component(ownerPtr)
    , m_Direction{ direction }
{
}

void zombieArena::Bullet::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();

    m_TimerHandle = diji::TimerManager::GetInstance().SetTimer([&]()
    {
        diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
    }, m_Lifetime, false);
}

void zombieArena::Bullet::Update()
{
    // todo: optimize the calls to CollisionSingleton and TimeSingleton
    const auto deltaMovement = m_Direction * m_Speed * diji::TimeSingleton::GetInstance().GetDeltaTime();
    m_TransformCompPtr->AddOffset(deltaMovement);

    // yeah I know on low fps bullets will fly by the enemy
    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr);
    for (const auto& collider : colliders)
    {
        if (!collider->GetParent()->HasComponent<Zombie>())
            continue;

        // Again I could decouple this but let's go simple for npw
        if (collider->GetParent()->GetComponent<Zombie>()->Hit())
            GameManager::GetInstance().OnZombieKilledEvent.Broadcast();

        diji::TimerManager::GetInstance().ClearTimer(m_TimerHandle);
        diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
        break;
    }
}

void zombieArena::Bullet::SetTextureAngle() const
{
    // todo: write helper functions for getting Angle from directions and turning radians into degrees
    const float angleDeg = std::atan2(m_Direction.y, m_Direction.x) * 180.0f / std::numbers::pi_v<float>;
    
    m_TextureCompPtr->SetRotationAngle(angleDeg);
}
