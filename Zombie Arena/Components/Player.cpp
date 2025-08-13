#include "Player.h"

#include <algorithm>
#include <numbers>
#include <SFML/Window/Mouse.hpp>

#include "PickUpBase.h"
#include "Pistol.h"
#include "../Core/GameState.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/GameStateManager.h"
#include "Engine/Singleton/PauseSingleton.h"
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

    m_TextureCompPtr->SetOriginToCenter();
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

void zombieArena::Player::Spawn(const sf::IntRect& arena, const int tileSize)
{
    m_TransformCompPtr->SetPosition(arena.size.x * 0.5f, arena.size.y * 0.5f);
    m_Arena = arena;

    m_TileSize = tileSize;
}

void zombieArena::Player::ResetStats()
{
    m_CurrentSpeed = START_SPEED;
    m_CurrentHealth = START_HEALTH;
    m_MaxHealth = START_HEALTH;
}

bool zombieArena::Player::Hit(const int damage)
{
    if (m_IsHit) return false;
    
    m_CurrentHealth -= damage;
    
    (void)diji::TimerManager::GetInstance().SetTimer([this]() { m_IsHit = false; }, INVINCIBILITY_TIME, false);

    return true;
}

void zombieArena::Player::UpgradeHealth()
{
    const int bonusHealth = static_cast<int>(START_HEALTH * 0.2f);
    m_MaxHealth += bonusHealth;
    Heal(bonusHealth);
}

void zombieArena::Player::Heal(const int amount)
{
    m_CurrentHealth = std::min(m_CurrentHealth += amount, m_MaxHealth);
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

