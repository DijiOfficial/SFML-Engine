#pragma once
#include "Engine/Interfaces/EventSystem.h"
#include "Engine/Singleton/Singleton.h"

namespace thomasWasLate
{
    enum class CurrentPlayer
    {
        Thomas = 0,
        Bob
    };
    
    class GameManager final : public diji::Singleton<GameManager>
    {
    public:
        [[nodiscard]] CurrentPlayer GetCurrentPlayer() const { return m_CurrentPlayer; }
        void SwitchPlayer();

        diji::Event<> OnPlayerSwitchedEvent;
    
    private:
        CurrentPlayer m_CurrentPlayer = CurrentPlayer::Thomas;
    };
}
