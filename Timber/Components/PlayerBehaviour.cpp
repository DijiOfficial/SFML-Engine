#include "PlayerBehaviour.h"

#include "../Interfaces/Observers.h"

void timber::PlayerBehaviour::Restart()
{
    Notify(static_cast<diji::MessageTypes>(MessageTypesDerived::Restart));
}
