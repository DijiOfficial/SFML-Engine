#include "WaveCounter.h"

#include "GameManager.h"

void zombieArena::WaveCounter::Init()
{
    ScoreCounter::Init();

    m_Score = GameManager::GetInstance().GetCurrentWave();
    ScoreChangeCheck();
}
