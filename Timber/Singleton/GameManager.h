#pragma once
#include "../Core/GameStates.h"
#include "Engine//Singleton/Singleton.h"

namespace timber
{
    class GameManager final : public diji::Singleton<GameManager>
    {
    public:
        GameState GetCurrentGameState() const { return m_CurrentGameState; }
        void SetNewGameState(const GameState& newGameState) { m_CurrentGameState = newGameState; }

    private:
        GameState m_CurrentGameState = GameState::Level;
    };
}