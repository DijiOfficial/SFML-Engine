#include "PickUpBase.h"

#include "GameManager.h"
#include "Player.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/SceneManager.h"

zombieArena::PickUpBase::PickUpBase(diji::GameObject* ownerPtr, const sf::IntRect& arena, std::string texturePath)
    : Component(ownerPtr)
    , m_TexturePath{std::move(texturePath )}
    , m_Arena{ arena }
{
    m_Arena = sf::IntRect{ arena.position + sf::Vector2i{ 25, 25 }, arena.size + sf::Vector2i{ 25, 25 } };    
}

zombieArena::PickUpBase::PickUpBase(diji::GameObject* ownerPtr, const sf::IntRect& arena, std::string texturePath, PickUpType type, int value)
    : Component(ownerPtr)
    , m_Type{ type }
    , m_TexturePath{std::move(texturePath )}
    , m_Arena{ arena }
    , m_Value{ value }
{
    m_Arena = sf::IntRect{ arena.position + sf::Vector2i{ 25, 25 }, arena.size + sf::Vector2i{ 25, 25 } };    
}

void zombieArena::PickUpBase::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();
    
    GetOwner()->GetComponent<diji::TextureComp>()->SetTexture(m_TexturePath);
    GetOwner()->GetComponent<diji::TextureComp>()->SetOriginToCenter();
    
    Spawn();
}

void zombieArena::PickUpBase::FixedUpdate()
{
    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr);
    for (const auto& collider : colliders)
    {
        if (!collider->GetParent()->HasComponent<Player>())
            continue;

        diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
        GameManager::GetInstance().OnPickedUpEvent.Broadcast(m_Type, m_Value);
        break;
    }
}

void zombieArena::PickUpBase::Spawn() const
{
    const int randomX = diji::RandNumber::GetRandomRangeInt(m_Arena.position.x, m_Arena.size.x);
    const int randomY = diji::RandNumber::GetRandomRangeInt(m_Arena.position.y, m_Arena.size.y);

    m_TransformCompPtr->SetPosition(static_cast<float>(randomX), static_cast<float>(randomY));

    // Removing the timer based respawn because it makes the game much worse having to run around for it to despawn in your face
    // (void)diji::TimerManager::GetInstance().SetTimer([&]()
    // {
    //     diji::SceneManager::GetInstance().SetPendingDestroy(GetOwner());
    // }, LIFETIME, false);
}


