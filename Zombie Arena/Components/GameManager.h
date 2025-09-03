#pragma once
#include "Engine/Singleton/Singleton.h"
#include "Engine/Interfaces/EventSystem.h"

//todo: add zombie counter and scene changes
// todo: increase core when zombie dies
namespace zombieArena
{
    enum class PickUpType;
    
    class GameManager final : public diji::Singleton<GameManager>
    {
    public:
        diji::Event<PickUpType, int> OnPickedUpEvent;
        diji::Event<> OnZombieKilledEvent;

        [[nodiscard]] int GetCurrentWave() const { return m_CurrentWave; }
    private:
        int m_CurrentWave = 1;
    };
}
