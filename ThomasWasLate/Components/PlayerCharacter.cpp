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

thomasWasLate::PlayerCharacter::PlayerCharacter(diji::GameObject* ownerPtr, const CurrentPlayer currPlayer)
    : Component{ ownerPtr }
    , m_CurrentCharacter{ currPlayer }
{
}

void thomasWasLate::PlayerCharacter::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();

    GameManager::GetInstance().OnPlayerSwitchedEvent.AddListener(this, &PlayerCharacter::RefreshView);
}

void thomasWasLate::PlayerCharacter::Start()
{
   m_CameraCompPtr = diji::SceneManager::GetInstance().GetGameObject("A_Camera")->GetComponent<diji::Camera>();
    
    SetCameraFollow();
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
