#include "CustomCommands.h"
#include "Engine/Core/GameObject.h"
#include "../Components/PlayerBehaviour.h"

void timber::Restart::Execute()
{
    GetGameActor()->GetComponent<PlayerBehaviour>()->Restart();
}

    