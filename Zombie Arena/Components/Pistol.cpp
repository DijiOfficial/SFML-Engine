#include "Pistol.h"

#include "Bullet.h"
#include "GameManager.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/TimerManager.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/Render.h"
#include "Engine/Collision/Collider.h"

zombieArena::Pistol::Pistol(diji::GameObject* ownerPtr)
    : Component(ownerPtr)
{
}

void zombieArena::Pistol::Init()
{
    const auto& gameManager = GameManager::GetInstance();
    m_TotalAmmo = gameManager.GetCurrentPlayerTotalBullets();
    m_MagCapacity = gameManager.GetCurrentPlayerBulletsInClip();
    m_FireRate = gameManager.GetPlayerFireRate();
    m_max_clip_capacity = gameManager.GetMaxClipSize();
    
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    const sf::Vector2f& position = m_TransformCompPtr->GetPosition();
    
    m_BulletTemplate = std::make_unique<diji::GameObject>();
    m_BulletTemplate->AddComponents<diji::Transform>(position.x, position.y);
    m_BulletTemplate->AddComponents<diji::TextureComp>("graphics/bullet.png");
    m_BulletTemplate->AddComponents<diji::Collider>();
    m_BulletTemplate->AddComponents<diji::Render>();
    m_BulletTemplate->AddComponents<Bullet>();
}

void zombieArena::Pistol::Start()
{
    OnAmmoChangedEvent.Broadcast(m_MagCapacity, m_TotalAmmo);
}

void zombieArena::Pistol::UpdatePosition(const sf::Vector2f& pos) const
{
    m_TransformCompPtr->SetPosition(pos);
}

void zombieArena::Pistol::FireWeapon(const bool isStart, const sf::Vector2f& direction)
{
    if (!isStart or !m_CanShoot) return;

    HandleWeaponFired(direction);
    m_CanShoot = false;

    (void)diji::TimerManager::GetInstance().SetTimer([&]() { m_CanShoot = true; }, m_FireRate, false);
}

void zombieArena::Pistol::Reload()
{
    if (m_TotalAmmo <= 0 || m_MagCapacity == m_max_clip_capacity)
        return;

    if (m_TotalAmmo < m_max_clip_capacity)
        m_MagCapacity = m_TotalAmmo;
    else
        m_MagCapacity = m_max_clip_capacity;
    
    m_TotalAmmo = std::max(0, m_TotalAmmo - m_max_clip_capacity);
    
    OnAmmoChangedEvent.Broadcast(m_MagCapacity, m_TotalAmmo);
}

void zombieArena::Pistol::SaveInfo() const
{
    auto& gameManager = GameManager::GetInstance();
    gameManager.SetCurrentPlayerTotalBullets(m_TotalAmmo);
    gameManager.SetCurrentPlayerBulletsInClip(m_MagCapacity);
}

void zombieArena::Pistol::HandleWeaponFired(const sf::Vector2f& direction)
{
    if (m_MagCapacity <= 0)
        return;

    HandleShot(direction);

    // Handle the sound, VFX, etc.
}

void zombieArena::Pistol::HandleShot(const sf::Vector2f& direction)
{
    const auto bullet = diji::SceneManager::GetInstance().SpawnGameObject("Y_Bullet", m_BulletTemplate.get(), m_TransformCompPtr->GetPosition());
    bullet->GetComponent<Bullet>()->SetDirection(direction);

    --m_MagCapacity;

    OnAmmoChangedEvent.Broadcast(m_MagCapacity, m_TotalAmmo);
}
