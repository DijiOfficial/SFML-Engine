#include "PlayerBehaviour.h"

#include "BranchBehaviour.h"
#include "../Singleton/GameManager.h"
#include "Engine/Core/GameObject.h"
#include "engine/Singleton/PauseSingleton.h"
#include "Engine/Components/Transform.h"

timber::PlayerBehaviour::PlayerBehaviour(diji::GameObject* ownerPtr)
    : Component(ownerPtr)
    , m_PlayerSide(BranchSide::Left)
{
}

void timber::PlayerBehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
}

void timber::PlayerBehaviour::Restart()
{
    GameManager::GetInstance().SetNewGameState(GameState::Level);
    OnRestartEvent.Broadcast();
    m_PlayerSide = BranchSide::Left;
    m_TransformCompPtr->SetPosition(580, 720);
}

void timber::PlayerBehaviour::MovePlayer(const BranchSide side)
{
    if (GameManager::GetInstance().GetCurrentGameState() != GameState::Level)
        return;
    
    m_PlayerSide = side;
    if (side == BranchSide::Left)
        m_TransformCompPtr->SetPosition(580, 720);
    else
        m_TransformCompPtr->SetPosition(1200, 720);
    
    OnPlayerMovedEvent.Broadcast(side == BranchSide::Left);
}

void timber::PlayerBehaviour::PauseGame()
{
    if (GameManager::GetInstance().GetCurrentGameState() != GameState::Level)
        return;
    
    diji::PauseSingleton::GetInstance().TogglePause();
    OnPauseEvent.Broadcast();
}
