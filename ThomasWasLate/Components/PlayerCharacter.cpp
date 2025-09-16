#include "PlayerCharacter.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Collision/Collider.h"
#include "../Singletons/GameManager.h"
#include "Engine/Components/Camera.h"

//temp
// #include "../Core/GameLoader.h"
// #include "Engine/Components/TextureComp.h"
// #include "Engine/Core/GameObject.h"

thomasWasLate::PlayerCharacter::PlayerCharacter(diji::GameObject* ownerPtr, const CurrentPlayer currPlayer)
    : Component{ ownerPtr }
    , m_CurrentCharacter{ currPlayer }
{
}

void thomasWasLate::PlayerCharacter::Start()
{
   m_CameraCompPtr = diji::SceneManager::GetInstance().GetGameObject("A_Camera")->GetComponent<diji::Camera>();
    
    SetCameraFollow();
}

void thomasWasLate::PlayerCharacter::RefreshView(const bool isSplitscreen) const
{
    if (isSplitscreen)
        diji::SceneManager::GetInstance().ChangePlayerViewCenter(static_cast<bool>(m_CurrentCharacter) ? 0 : 1, GetOwner()->GetComponent<diji::Collider>()->GetCenter());
    else
        SetCameraFollow();
}

void thomasWasLate::PlayerCharacter::SetCameraFollow() const
{
    if (m_CurrentCharacter == GameManager::GetInstance().GetCurrentPlayer())
    {
        m_CameraCompPtr->SetFollow(GetOwner());
        m_CameraCompPtr->SetOffsetCamera(GetOwner()->GetComponent<diji::Collider>()->GetCenter());
    }
}
