#include "PlayerBehaviour.h"

#include <iostream>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "BranchBehaviour.h"
#include "../Singleton/GameManager.h"
#include "Engine/Core/GameObject.h"
#include "engine/Singleton/PauseSingleton.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Interfaces/ISoundSystem.h"

timber::PlayerBehaviour::PlayerBehaviour(diji::GameObject* ownerPtr)
    : Component(ownerPtr)
    , m_PlayerSide(BranchSide::Left)
{
}

void timber::PlayerBehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_RenderCompPtr = GetOwner()->GetComponent<diji::Render>();
    m_RenderCompPtr->EnableRender();
}

void timber::PlayerBehaviour::Restart()
{
    GameManager::GetInstance().SetNewGameState(GameState::Level);
    OnRestartEvent.Broadcast();
    m_PlayerSide = BranchSide::Left;
    m_TransformCompPtr->SetPosition(580, 720);
    m_RenderCompPtr->EnableRender();
}

void timber::PlayerBehaviour::MovePlayer(const BranchSide side)
{
    if (GameManager::GetInstance().GetCurrentGameState() != GameState::Level)
        return;
    
    m_PlayerSide = side;
    if (side == BranchSide::Left)
        m_TransformCompPtr->SetPosition(580, 720);
    else
        m_TransformCompPtr->SetPosition(1200, 720);

    diji::ServiceLocator::GetSoundSystem().AddSoundRequest("sound/chop.wav", false);
    
    OnPlayerMovedEvent.Broadcast(side == BranchSide::Left);
}

void timber::PlayerBehaviour::PauseGame()
{
    if (GameManager::GetInstance().GetCurrentGameState() != GameState::Level)
        return;
    
    diji::PauseSingleton::GetInstance().TogglePause();
    OnPauseEvent.Broadcast();
}

void timber::PlayerBehaviour::DeathHandle()
{
    diji::PauseSingleton::GetInstance().SetIsPaused(true);
    GameManager::GetInstance().SetNewGameState(GameState::GameOver);
    m_RenderCompPtr->DisableRender();
    
    diji::ServiceLocator::GetSoundSystem().AddSoundRequest("sound/death.wav", false);
    
    OnDeathEvent.Broadcast();
    OnPauseEvent.Broadcast();
}
