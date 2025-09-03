#include "CustomCommands.h"

#include "../Components/GameManager.h"
#include "../Components/Player.h"
#include "../Core/GameState.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/GameStateManager.h"
#include "Engine/Singleton/SceneManager.h"

zombieArena::MovePlayer::MovePlayer(diji::GameObject* actor, const Movement movement, const bool isStart)
    : GameActorCommands(actor)
    , m_IsStart{ isStart }
{
    m_PlayerCompPtr = actor->GetComponent<Player>();

    switch (movement)
    {
    case Movement::Left:
        m_Direction = {-1, 0};
        break;
    case Movement::Right:
        m_Direction = {1, 0};
        break;
    case Movement::Top:
        m_Direction = {0, -1};
        break;
    case Movement::Bottom:
        m_Direction = {0, 1};
        break;
    }
}

void zombieArena::MovePlayer::Execute()
{
    auto playerDir = m_PlayerCompPtr->GetDirection();

    if (m_IsStart)
        playerDir += m_Direction;
    else
        playerDir -= m_Direction;

    // Clamp the direction values to ensure they stay within the range [-1, 1]
    playerDir.x = std::clamp(playerDir.x, -1.0f, 1.0f);
    playerDir.y = std::clamp(playerDir.y, -1.0f, 1.0f);

    m_PlayerCompPtr->SetDirection(playerDir);
}

zombieArena::Aim::Aim(diji::GameObject* actor)
    : GameActorCommands(actor)
{
    m_PlayerCompPtr = actor->GetComponent<Player>();
}

void zombieArena::Aim::Execute(const sf::Vector2i& mousePos)
{
    m_PlayerCompPtr->OrientPlayer(mousePos);
}

void zombieArena::Pause::Execute()
{
    if (static_cast<ZombieGameState>(diji::GameStateManager::GetInstance().GetCurrentGameState()) == ZombieGameState::Level)
        GetGameActor()->GetComponent<Player>()->PauseGame();
}

zombieArena::Shoot::Shoot(diji::GameObject* actor, const bool isStart)
    : GameActorCommands(actor)
    , m_IsStart{ isStart }
{
    m_PlayerCompPtr = actor->GetComponent<Player>();
}

void zombieArena::Shoot::Execute()
{
    if (m_PlayerCompPtr)
        m_PlayerCompPtr->Shoot(m_IsStart);
}

zombieArena::Reload::Reload(diji::GameObject* actor)
    : GameActorCommands(actor)
{
    m_PlayerCompPtr = actor->GetComponent<Player>();
}

void zombieArena::Reload::Execute()
{
    m_PlayerCompPtr->Reload();
}

zombieArena::Start::Start(diji::GameObject* actor, const ZombieGameState nextState)
    : GameActorCommands(actor)
    , m_NextState{ nextState }
{
}

void zombieArena::Start::Execute()
{
    diji::SceneManager::GetInstance().SetNextSceneToActivate(static_cast<int>(m_NextState));
}

zombieArena::UpgradeChoice::UpgradeChoice(diji::GameObject* actor, const UpgradeType upgradeType)
    : GameActorCommands(actor)
    , m_UpgradeType{ upgradeType }
{
}

void zombieArena::UpgradeChoice::Execute()
{
    GameManager::GetInstance().Upgrade(m_UpgradeType);

    diji::SceneManager::GetInstance().SetNextSceneToActivate(static_cast<int>(ZombieGameState::Level));
}
