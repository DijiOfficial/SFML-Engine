#include "CustomCommands.h"
#include "../Components/Paddle.h"
#include "Engine/Core/GameObject.h"

pong::MovePlayer::MovePlayer(diji::GameObject* actor, const Movement movement, const bool isStart)
    : GameActorCommands{ actor }
    , m_Movement{ movement }
    , m_IsStart{ isStart }
{
}

void pong::MovePlayer::Execute()
{
    if (m_Movement == Movement::Left)
        GetGameActor()->GetComponent<Paddle>()->SetIsMovingLeft(m_IsStart);
    else
        GetGameActor()->GetComponent<Paddle>()->SetIsMovingRight(m_IsStart);
}
