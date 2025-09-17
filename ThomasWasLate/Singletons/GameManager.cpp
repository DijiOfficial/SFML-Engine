#include "GameManager.h"

#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Engine/Collision/CollisionSingleton.h"

void thomasWasLate::GameManager::SwitchPlayer()
{
    m_CurrentPlayer = static_cast<bool>(m_CurrentPlayer) ? CurrentPlayer::Thomas : CurrentPlayer::Bob;

    OnPlayerSwitchedEvent.Broadcast();
}

void thomasWasLate::GameManager::LoadLevel()
{
    ReadLevelInfo(LoadInformation());

    CreateWorldCollision();

    OnNewLevelLoadedEvent.Broadcast();
}

std::string thomasWasLate::GameManager::LoadInformation()
{
    switch (m_CurrentLevel) // if you're going to read from a file put this information in the fucking file
    {
    case 1:
        m_StartPosition.x = 100;
        m_StartPosition.y = 100;
        m_LevelTimeLimit = 30.0f;
        break;
    case 2:
        m_StartPosition.x = 100;
        m_StartPosition.y = 3600;
        m_LevelTimeLimit = 100.0f;
        break;
    case 3:
        m_StartPosition.x = 1250;
        m_StartPosition.y = 0;
        m_LevelTimeLimit = 30.0f;
        break;
    case 4:
        m_StartPosition.x = 50;
        m_StartPosition.y = 200;
        m_LevelTimeLimit = 50.0f;
        break;
    default:
        throw std::runtime_error("Invalid Level.");
    }

    return std::format("../ThomasWasLate/Resources/levels/level{}.txt", m_CurrentLevel);
}

void thomasWasLate::GameManager::ReadLevelInfo(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (!file.is_open())
        throw std::runtime_error("Could not open level file: " + filepath);

    std::string line;
    m_Rows = 0;
    m_Cols = 0;
    m_LevelInfo = std::vector<int>();

    while (std::getline(file, line))
    {
        int colCount = 0;

        for (const char c : line)
        {
            if (std::isdigit(c))
            {
                int number = c - '0';
                m_LevelInfo.push_back(number);
                ++colCount;
            }
        }

        if (m_Rows == 0)
            m_Cols = colCount;

        ++m_Rows;
    }

    
    file.close();
}

void thomasWasLate::GameManager::CreateWorldCollision()
{
    constexpr float kTileSize = 50.0f;

    auto& collision = diji::CollisionSingleton::GetInstance();

    for (int row = 0; row < m_Rows; ++row)
    {
        int col = 0;
        while (col < m_Cols)
        {
            const int idx = row * m_Cols + col;
            if (m_LevelInfo[idx] == 1)
            {
                const int startC = col;
                while (col < m_Cols && m_LevelInfo[row * m_Cols + col] == 1)
                    ++col;

                const int len = col - startC;

                diji::Rectf rect{};
                rect.left   = static_cast<float>(startC) * kTileSize;
                rect.bottom = static_cast<float>(row) * kTileSize;
                rect.width  = static_cast<float>(len) * kTileSize;
                rect.height = kTileSize;

                collision.ParseRectInLevelCollider(rect);
            }
            else
            {
                ++col;
            }
        }
    }
}
