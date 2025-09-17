#include "PlayerCharacter.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Collision/Collider.h"
#include "../Singletons/GameManager.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/Transform.h"

//temp
// #include "../Core/GameLoader.h"
// #include "Engine/Components/TextureComp.h"
// #include "Engine/Core/GameObject.h"

thomasWasLate::PlayerCharacter::PlayerCharacter(diji::GameObject* ownerPtr, const CurrentPlayer currPlayer, const float jumpTime)
    : Component{ ownerPtr }
    , m_CurrentCharacter{ currPlayer }
    , m_MaxJumpTime{ jumpTime }
{
}

void thomasWasLate::PlayerCharacter::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();

    GameManager::GetInstance().OnPlayerSwitchedEvent.AddListener(this, &PlayerCharacter::RefreshView);
    GameManager::GetInstance().OnNewLevelLoadedEvent.AddListener(this, &PlayerCharacter::OnNewLevelLoaded);

}

void thomasWasLate::PlayerCharacter::Start()
{
   m_CameraCompPtr = diji::SceneManager::GetInstance().GetGameObject("A_Camera")->GetComponent<diji::Camera>();
    
    SetCameraFollow();
}

void thomasWasLate::PlayerCharacter::Update()
{
    // don't copy this, it's shit I dont care I just need it to work now
    diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
    newCollisionBox.bottom += GRAVITY * diji::TimeSingleton::GetInstance().GetDeltaTime() + m_ColliderCompPtr->GetOffset().y;
    
    bool isLevelDone = false;
    bool isPlayerColliding = false;
    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr, newCollisionBox);
    for (const auto& collider : colliders)
    {
        // other collision
        if (!collider->GetParent())
        {
            if (collider->GetTag() == "goal")
            {
                isLevelDone = true;
            }
            continue;
        }

        // player collision
        if (collider->GetParent()->HasComponent<PlayerCharacter>())
        {
            isPlayerColliding = true;
        }
    }

    if (isLevelDone && isPlayerColliding)
    {
        GameManager::GetInstance().SetLevelCleared();
    }
}

void thomasWasLate::PlayerCharacter::FixedUpdate()
{
    diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
    newCollisionBox.bottom += GRAVITY * diji::TimeSingleton::GetInstance().GetFixedUpdateDeltaTime();

    // check for collision with world
    if (diji::CollisionSingleton::GetInstance().IsCollidingWithWorld(newCollisionBox))
    {
        if (m_IsOnGround)
            return;
        
        m_IsOnGround = true;
        m_JumpTime = 0.0f;

        // Snap to ground
        m_TransformCompPtr->SetPosition(m_TransformCompPtr->GetPosition().x, std::round((newCollisionBox.bottom - m_ColliderCompPtr->GetOffset().y) / 50) * 50 - 1.f);
        
        return;
    }

    if (!m_IsJumping)
        m_IsOnGround = false;

    // Check Player Collision and Others
    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr, newCollisionBox);
    for (const auto& collider : colliders)
    {
        // other collision
        if (!collider->GetParent())
        {
            const auto& tag = collider->GetTag();
            
            if (tag == "water" || tag == "lava")
            {
                m_TransformCompPtr->SetPosition(m_SpawnPoint);
            }

            if (tag == "void")
            {
                m_TransformCompPtr->SetPosition(m_SpawnPoint);
            }
            
            return;
        }

        if (m_IsJumping)
            break;
        
        // player collision
        if (collider->GetParent()->HasComponent<PlayerCharacter>())
        {
            const auto otherBox = collider->GetCollisionBox();

            // only snap if we are above the other player
            const float myBottomEdge = newCollisionBox.bottom + newCollisionBox.height;
            const float otherTopEdge = otherBox.bottom + 5;
            if (myBottomEdge > otherTopEdge)
                break;
            
            m_IsOnGround = true;
            m_JumpTime = 0.0f;

            // Snap to player head
            m_TransformCompPtr->SetPosition(m_TransformCompPtr->GetPosition().x, otherBox.bottom - newCollisionBox.height - m_ColliderCompPtr->GetOffset().y - 1.f);

            return;
        }
    }

    m_TransformCompPtr->AddOffset(0.f, GRAVITY * diji::TimeSingleton::GetInstance().GetFixedUpdateDeltaTime());
}

void thomasWasLate::PlayerCharacter::RefreshView(const bool isSplitscreen) const
{
    if (isSplitscreen)
        diji::SceneManager::GetInstance().SetViewParameters(static_cast<bool>(m_CurrentCharacter) ? 0 : 1, GetOwner()->GetComponent<diji::Transform>(), true, sf::Vector2f{ 25.f, 25.f });
    else
        SetCameraFollow();
}

void thomasWasLate::PlayerCharacter::Move(const sf::Vector2f& direction) const
{
    diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
    newCollisionBox.left += direction.x * m_Speed * diji::TimeSingleton::GetInstance().GetDeltaTime();

    // check for collision with world
    if (diji::CollisionSingleton::GetInstance().IsCollidingWithWorld(newCollisionBox))
        return;

    // Check collision with others
    const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr);
    for (const auto& collider : colliders)
    {
        if (!collider->GetParent())
            continue;
        
        if (collider->GetParent()->HasComponent<PlayerCharacter>())
        {
            const auto otherBox = collider->GetCollisionBox();

            if (direction.x > 0.f && otherBox.left > newCollisionBox.left)
                return;
            if (direction.x < 0.f && otherBox.left < newCollisionBox.left)
                return;
        }
    }
    
    m_TransformCompPtr->AddOffset(direction * m_Speed * diji::TimeSingleton::GetInstance().GetDeltaTime());
}

void thomasWasLate::PlayerCharacter::SetCameraFollow() const
{
    if (m_CurrentCharacter == GameManager::GetInstance().GetCurrentPlayer())
    {
        const auto& collision = GetOwner()->GetComponent<diji::Collider>()->GetCollisionBox();
        m_CameraCompPtr->SetFollow(GetOwner());
        m_CameraCompPtr->SetOffsetCamera(sf::Vector2f{ collision.width * 0.5f, collision.height * 0.5f });
    }
}

void thomasWasLate::PlayerCharacter::OnNewLevelLoaded()
{
    m_TransformCompPtr->SetPosition(static_cast<sf::Vector2f>(GameManager::GetInstance().GetStartPosition()));

    if (m_CurrentCharacter == CurrentPlayer::Bob)
        m_TransformCompPtr->AddOffset(0.f, -100.f);

    m_SpawnPoint = m_TransformCompPtr->GetPosition();
}

void thomasWasLate::PlayerCharacter::CheckForBoosting()
{
    if (m_IsBoosting)
    {
        m_IsBoosting = false;
        diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
        newCollisionBox.bottom -= GRAVITY * 3 * diji::TimeSingleton::GetInstance().GetDeltaTime();

        const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr, newCollisionBox);
        for (const auto& collider : colliders)
        {
            // other collision
            if (!collider->GetParent())
                continue;

            // player collision
            if (!collider->GetParent()->HasComponent<PlayerCharacter>())
                continue;

            collider->GetParent()->GetComponent<PlayerCharacter>()->ClearJump();
            const auto& otherBox = collider->GetCollisionBox();
            const auto& transform = collider->GetParent()->GetComponent<diji::Transform>();
            transform->SetPosition(transform->GetPosition().x, newCollisionBox.bottom - otherBox.height - collider->GetOffset().y + 6.f);
        } 
    }
}

void thomasWasLate::PlayerCharacter::Jump(const bool ignoreTimer)
{
    if (!m_IsOnGround)
        return;

    m_IsJumping = true;
    
    // Update how long the jump has been going
    m_JumpTime += diji::TimeSingleton::GetInstance().GetDeltaTime();
    
    if (m_JumpTime < m_MaxJumpTime || ignoreTimer)
    {
        diji::Rectf newCollisionBox = m_ColliderCompPtr->GetCollisionBox();
        newCollisionBox.bottom -= GRAVITY * 3 * diji::TimeSingleton::GetInstance().GetDeltaTime();

        // check for collision with world
        if (diji::CollisionSingleton::GetInstance().IsCollidingWithWorld(newCollisionBox))
            return;
        
        // handle collision with players
        const auto& colliders = diji::CollisionSingleton::GetInstance().IsColliding(m_ColliderCompPtr, newCollisionBox);
        for (const auto& collider : colliders)
        {
            if (ignoreTimer)
                break;
            
            // other collision
            if (!collider->GetParent())
                continue;

            // player collision
            if (collider->GetParent()->HasComponent<PlayerCharacter>())
            {
                const auto otherBox = collider->GetCollisionBox();
                const float myTopEdge = newCollisionBox.bottom;
                const float otherBottomEdge = otherBox.bottom + otherBox.height;
                if (myTopEdge <= otherBottomEdge)
                {
                    m_IsBoosting = true;
                    collider->GetParent()->GetComponent<PlayerCharacter>()->Jump(true);
                    // return;
                }
            }
        }
        
        m_TransformCompPtr->AddOffset(0.f, -GRAVITY * 3 * diji::TimeSingleton::GetInstance().GetDeltaTime());
        return;
    }

    CheckForBoosting();

    m_IsJumping = false;
}

void thomasWasLate::PlayerCharacter::ClearJump()
{
    m_IsOnGround = false;
    m_JumpTime = 5.0f;
    m_IsJumping = false;
    
    CheckForBoosting();
}

