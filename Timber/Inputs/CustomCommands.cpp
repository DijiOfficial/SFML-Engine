#include "CustomCommands.h"
#include "Engine/Core/GameObject.h"
#include "../Components/PlayerBehaviour.h"
#include "../Components/BranchBehaviour.h"

void timber::Restart::Execute()
{
    GetGameActor()->GetComponent<PlayerBehaviour>()->Restart();
}

timber::MovePlayer::MovePlayer(diji::GameObject* actor, const Direction dir)
    : GameActorCommands{ actor }
    , m_Direction{ dir }
{
}

void timber::MovePlayer::Execute()
{
    const BranchSide side = m_Direction == Direction::Left ? BranchSide::Left : BranchSide::Right;
    GetGameActor()->GetComponent<PlayerBehaviour>()->MovePlayer(side);
}

void timber::Pause::Execute()
{
    GetGameActor()->GetComponent<PlayerBehaviour>()->PauseGame();
}

    