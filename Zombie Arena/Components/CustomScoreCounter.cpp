#include "CustomScoreCounter.h"

#include "GameManager.h"

void zombieArena::CustomScoreCounter::Start()
{
    ScoreCounter::Start();

    OnScoreIncreasedEvent.Broadcast(m_Score);
}

void zombieArena::CustomScoreCounter::SaveScore()
{
    GameManager::GetInstance().SetCurrentPlayerScore(m_Score);

    OnScoreSetEvent.ClearListeners();
}
