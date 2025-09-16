#include "Player.h"

#include <algorithm>
#include <numbers>
#include <SFML/Window/Mouse.hpp>

#include "GameManager.h"
#include "PickUpBase.h"
#include "Pistol.h"
#include "Zombie.h"
#include "../Core/GameState.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/Sprite.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/GameStateManager.h"
#include "Engine/Singleton/PauseSingleton.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"
#include "Engine/Singleton/TimeSingleton.h"

zombieArena::Player::Player(diji::GameObject* ownerPtr, const sf::IntRect& arena)
    : Component(ownerPtr)
{
    m_Arena = { sf::Vector2i{ arena.position.x + 25, arena.position.y + 25},  sf::Vector2i{ arena.size.x - 50, arena.size.y - 50 }};
}

void zombieArena::Player::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();
    m_CameraCompPtr = GetOwner()->GetComponent<diji::Camera>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();

    m_TextureCompPtr->SetOriginToCenter();
    const auto& gameManager = GameManager::GetInstance();
    m_MaxHealth = gameManager.GetMaxHealth();
    m_CurrentHealth = gameManager.GetPlayerHealth();
    m_CurrentSpeed = gameManager.GetRunSpeed();
}

void zombieArena::Player::Start()
{
    diji::SceneManager::GetInstance().GetGameObject("A_Background")->GetComponent<diji::Sprite>()->GenerateMap();
}

void zombieArena::Player::Update()
{
    // clamp the position to the arena bounds
    auto newPosition = m_TransformCompPtr->GetPosition() + m_Direction * m_CurrentSpeed * diji::TimeSingleton::GetInstance().GetDeltaTime();
    newPosition.x = std::clamp(newPosition.x, static_cast<float>(m_Arena.position.x),static_cast<float>(m_Arena.position.x + m_Arena.size.x));
    newPosition.y = std::clamp(newPosition.y, static_cast<float>(m_Arena.position.y), static_cast<float>(m_Arena.position.y + m_Arena.size.y));
    m_TransformCompPtr->SetPosition(newPosition);
    
    // Orient the player to mouse position
    if (!m_CameraCompPtr) return;
    
    const sf::Vector2f playerPos = m_TransformCompPtr->GetPosition();
    m_LookingDirection = static_cast<sf::Vector2f>(m_CameraCompPtr->GetMouseWorldPosition(m_LastMousePos)) - playerPos;

    // todo: write helper functions for getting Angle from directions and turning radians into degrees
    const float angleDeg = std::atan2(m_LookingDirection.y, m_LookingDirection.x) * 180.0f / std::numbers::pi_v<float>;
    
    m_TextureCompPtr->SetRotationAngle(angleDeg);

    m_PistolCompPtr->UpdatePosition(playerPos);
}

void zombieArena::Player::FixedUpdate()
{
    if (m_IsHit) return;

    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr);
    for (const auto& collider : colliders)
    {
        if (!collider->GetParent()->HasComponent<Zombie>())
            continue;

        Hit(10);
        break;
    }
}

void zombieArena::Player::OnDestroy()
{
    diji::TimerManager::GetInstance().ClearTimer(m_InvincibilityTimerHandle);
}

void zombieArena::Player::Spawn(const sf::IntRect& arena, const int tileSize)
{
    m_TransformCompPtr->SetPosition(static_cast<float>(arena.size.x) * 0.5f, static_cast<float>(arena.size.y) * 0.5f);
    m_Arena = arena;

    m_TileSize = tileSize;
}

bool zombieArena::Player::Hit(const int damage)
{
    if (m_IsHit) return false;

    m_IsHit = true;
    m_CurrentHealth -= damage;
    OnHealthChangeEvent.Broadcast(m_CurrentHealth);
    
    if (m_CurrentHealth <= 0)
    {
        OnDeathEvent.Broadcast();
        return true;
    }
    
    m_InvincibilityTimerHandle = diji::TimerManager::GetInstance().SetTimer([this]() { m_IsHit = false; }, INVINCIBILITY_TIME, false);

    return true;
}

void zombieArena::Player::HandlePickups(const PickUpType type, const int value)
{
    switch (type)
    {
    case PickUpType::HEALTH:
        Heal(value);
        break;
    case PickUpType::AMMO:
        GiveAmmo(value);
        break;
    case PickUpType::NONE:
    default:
        break;
    }
}

void zombieArena::Player::Heal(const int amount)
{
    m_CurrentHealth = std::min(m_CurrentHealth += amount, m_MaxHealth);
    OnHealthChangeEvent.Broadcast(m_CurrentHealth);
}

void zombieArena::Player::OrientPlayer(const sf::Vector2i& mousePos)
{
    m_LastMousePos = mousePos;
}

void zombieArena::Player::PauseGame()
{
    if (static_cast<ZombieGameState>(diji::GameStateManager::GetInstance().GetCurrentGameState()) != ZombieGameState::Level) // can only pause during the level change state?
        return;
    
    diji::PauseSingleton::GetInstance().TogglePause();
    OnPauseEvent.Broadcast();
}

void zombieArena::Player::GivePistol(const diji::GameObject* object)
{
    m_PistolCompPtr = object->GetComponent<Pistol>();
}

void zombieArena::Player::Shoot(const bool isStart) const
{
    if (!m_PistolCompPtr)
        return;

    m_PistolCompPtr->FireWeapon(isStart, m_LookingDirection);
}

void zombieArena::Player::Reload() const
{
    m_PistolCompPtr->Reload();
}

void zombieArena::Player::GiveAmmo(const int value) const
{
    m_PistolCompPtr->GiveAmmo(value);
}

