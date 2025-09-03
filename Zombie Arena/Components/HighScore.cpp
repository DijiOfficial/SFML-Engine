#include "HighScore.h"

#include <fstream>
#include <string>

void zombieArena::HighScore::Init()
{
    ScoreCounter::Init();
    
    std::ifstream file{ "Resources/HighScore.txt" };
    if (!file.is_open())
        return;
    
    file >> m_Score;
    file.close();
}

void zombieArena::HighScore::SaveHighScore() const
{
    // could dirty flag save it only when score is higher than previous high score
    const std::string fileName{ "Resources/HighScore.txt" };
    std::ofstream file{ fileName, std::ios_base::out | std::ios_base::trunc };
    const std::string text{ std::to_string(m_Score) };
    file << text;
    file.flush();
    file.close();
}

void zombieArena::HighScore::UpdateScore(const int value)
{
    if (value <= m_Score)
        return;
    
    m_Score = value;
    ScoreChangeCheck();
}
