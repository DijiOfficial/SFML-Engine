#include "CustomCommands.h"

#include "Engine/Singleton/SceneManager.h"

void thomasWasLate::SwitchSplitScreenView::Execute()
{
    m_IsMultiplayer = !m_IsMultiplayer;
    diji::SceneManager::GetInstance().SetMultiplayerSplitScreen(m_IsMultiplayer ? 2 : 1);
}
