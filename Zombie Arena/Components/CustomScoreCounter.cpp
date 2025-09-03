#include "CustomScoreCounter.h"

#include "GameManager.h"

void zombieArena::CustomScoreCounter::SaveScore() const
{
    GameManager::GetInstance().SetCurrentPlayerScore(m_Score);
}
