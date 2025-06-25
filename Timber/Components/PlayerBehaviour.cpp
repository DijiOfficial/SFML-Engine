#include "PlayerBehaviour.h"

#include "../Interfaces/Observers.h"
#include "BranchBehaviour.h"

timber::PlayerBehaviour::PlayerBehaviour(diji::GameObject* ownerPtr)
    : Component(ownerPtr)
    , m_PlayerSide(BranchSide::Left)
{
}

void timber::PlayerBehaviour::Restart()
{
    Notify(static_cast<diji::MessageTypes>(MessageTypesDerived::Restart));
}
