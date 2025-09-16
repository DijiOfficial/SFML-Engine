#include "GameManager.h"

void thomasWasLate::GameManager::SwitchPlayer()
{
    m_CurrentPlayer = static_cast<bool>(m_CurrentPlayer) ? CurrentPlayer::Bob : CurrentPlayer::Thomas;
}
