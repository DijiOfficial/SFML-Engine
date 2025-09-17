#include "CustomCommands.h"
#include "Engine/Singleton/SceneManager.h"
#include "../Components/PlayerCharacter.h"
#include "../Singletons/GameManager.h"

thomasWasLate::SwitchSplitScreenView::SwitchSplitScreenView(diji::GameObject* actor, PlayerCharacter* thomas, PlayerCharacter* bob)
    : GameActorCommands{ actor }
    , m_Thomas{ thomas }
    , m_Bob{ bob }
{
}

void thomasWasLate::SwitchSplitScreenView::Execute()
{
    m_IsMultiplayer = !m_IsMultiplayer;
    diji::SceneManager::GetInstance().SetMultiplayerSplitScreen(m_IsMultiplayer ? 2 : 1);

    m_Thomas->RefreshView(m_IsMultiplayer);
    m_Bob->RefreshView(m_IsMultiplayer);
}

thomasWasLate::MoveCharacter::MoveCharacter(diji::GameObject* actor, const sf::Vector2f& direction)
    : GameActorCommands{ actor }
    , m_Direction{ direction }
{
    m_Character = actor->GetComponent<PlayerCharacter>();
}

void thomasWasLate::MoveCharacter::Execute()
{
    m_Character->Move(m_Direction);
}

void thomasWasLate::SwitchCharacter::Execute()
{
    GameManager::GetInstance().SwitchPlayer();
}

thomasWasLate::CharacterJump::CharacterJump(diji::GameObject* actor, const bool isJumping)
    : GameActorCommands{ actor }
    , m_IsJumping{ isJumping }
{
    m_Character = actor->GetComponent<PlayerCharacter>();
}

void thomasWasLate::CharacterJump::Execute()
{
    if (m_IsJumping)
        m_Character->Jump();
    else
        m_Character->ClearJump();
}

