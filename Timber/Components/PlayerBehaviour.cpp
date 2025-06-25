#include "PlayerBehaviour.h"

#include "BranchBehaviour.h"
#include "engine/Singleton/PauseSingleton.h"

timber::PlayerBehaviour::PlayerBehaviour(diji::GameObject* ownerPtr)
    : Component(ownerPtr)
    , m_PlayerSide(BranchSide::Left)
{
}

void timber::PlayerBehaviour::Restart()
{
    OnRestartEvent.Broadcast();
}

void timber::PlayerBehaviour::MovePlayer(const BranchSide side)
{
    m_PlayerSide = side;
    OnPlayerMovedEvent.Broadcast();
}

void timber::PlayerBehaviour::PauseGame()
{
    diji::PauseSingleton::GetInstance().TogglePause();
    OnPauseEvent.Broadcast();
}
