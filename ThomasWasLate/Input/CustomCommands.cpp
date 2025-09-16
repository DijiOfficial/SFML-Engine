#include "CustomCommands.h"
#include "Engine/Singleton/SceneManager.h"
#include "../Components/PlayerCharacter.h"

thomasWasLate::SwitchSplitScreenView::SwitchSplitScreenView(diji::GameObject* actor, PlayerCharacter* thomas, PlayerCharacter* bob)
    : GameActorCommands{ actor }
    , m_Thomas{ thomas }
    , m_Bob{ bob }
{
}

void thomasWasLate::SwitchSplitScreenView::Execute()
{
    m_IsMultiplayer = !m_IsMultiplayer;
    diji::SceneManager::GetInstance().SetMultiplayerSplitScreen(m_IsMultiplayer ? 2 : 1);

    m_Thomas->RefreshView(m_IsMultiplayer);
    m_Bob->RefreshView(m_IsMultiplayer);
}
