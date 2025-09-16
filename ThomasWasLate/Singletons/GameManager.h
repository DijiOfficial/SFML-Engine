#pragma once
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
    
    private:
        CurrentPlayer m_CurrentPlayer = CurrentPlayer::Thomas;
    };
}
