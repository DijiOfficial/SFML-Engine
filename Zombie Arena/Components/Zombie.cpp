#include "Zombie.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Collision/Collider.h"

#include <numbers>

// TODO: DONT FORGET TO DELETE THEM WHEN THEY DIE
zombieArena::Zombie::Zombie(diji::GameObject* ownerPtr, const diji::GameObject* target, const ZombieType type)
    : Component(ownerPtr)
    , m_Type{ type }
{
    m_PendingTarget = target;
}

void zombieArena::Zombie::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();
    
    m_TransformCompPtr->SetTarget(m_PendingTarget);

    // I don't know a cleaner way
    m_PendingTarget = nullptr; // discard to free memory use
    
    SetZombieStats();
}

// Game gets laggy quite fast with too many zombies. first likely because the game runs on 1 core only, second likely because of the seek behaviour 
void zombieArena::Zombie::Update()
{
    if (m_IsDead)
        return;
    
    // todo: create a behaviour system like in GPP if going to expand on behaviours
    m_TransformCompPtr->Seek(m_Speed);

    const sf::Vector2f playerPos = m_TransformCompPtr->GetPosition();
    const sf::Vector2f direction = m_TransformCompPtr->GetTarget()->GetPosition() - playerPos;

    // todo: write helper functions for getting Angle from directions and turning radians into degrees
    const float angleDeg = std::atan2(direction.y, direction.x) * 180.0f / std::numbers::pi_v<float>;
    
    m_TextureCompPtr->SetRotationAngle(angleDeg);
}

bool zombieArena::Zombie::Hit()
{
    --m_Health;

    if (m_Health > 0)
        return false;

    m_IsDead = true;
    m_TextureCompPtr->SetTexture("graphics/blood.png");
    diji::CollisionSingleton::GetInstance().RemoveCollider(GetOwner()->GetComponent<diji::Collider>());
    return true;
}

void zombieArena::Zombie::SetTarget(const diji::GameObject* target) const
{
    m_TransformCompPtr->SetTarget(target);
}

void zombieArena::Zombie::SetType(const ZombieType type)
{
    m_Type = type;
    
    SetZombieStats();

    GetOwner()->GetComponent<diji::Collider>()->UpdateColliderFromTexture();
}

void zombieArena::Zombie::SetZombieStats()
{
    switch (m_Type)
    {
    case ZombieType::BLOATER:
        m_Speed = BLOATER_SPEED;
        m_Health = BLOATER_HEALTH;
        m_TextureCompPtr->SetTexture("graphics/bloater.png");
        break;
    case ZombieType::CHASER:
        m_Speed = CHASER_SPEED;
        m_Health = CHASER_HEALTH;
        m_TextureCompPtr->SetTexture("graphics/chaser.png");
        break;
    case ZombieType::CRAWLER:
        m_Speed = CRAWLER_SPEED;
        m_Health = CRAWLER_HEALTH;
        m_TextureCompPtr->SetTexture("graphics/crawler.png");
        break;
    case ZombieType::TOTAL_ZOMBIE_TYPES:
        break;
    }
    
    const float modifier = diji::RandNumber::GetRandomRangeFloat(0.7f, 1.0f);
    m_Speed *= modifier;

    m_TextureCompPtr->SetOriginToCenter();
}
