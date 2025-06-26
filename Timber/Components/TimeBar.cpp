#include "TimeBar.h"

#include "../Singleton/GameManager.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/RectRender.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Singleton/PauseSingleton.h"

void timber::TimeBar::Init()
{
    m_RectRenderCompPtr = GetOwner()->GetComponent<diji::RectRender>();
}

void timber::TimeBar::Update()
{
    // std::cout << m_RemainingTime << std::endl;
    m_RemainingTime -= diji::TimeSingleton::GetInstance().GetDeltaTime(); // optimize this call?

    m_RectRenderCompPtr->GetRectangle().setSize(sf::Vector2f{ m_WidthPerSecond * m_RemainingTime, m_RectRenderCompPtr->GetRectangle().getSize().y});

    if (m_RemainingTime <= 0.0f)
    {
        diji::PauseSingleton::GetInstance().SetIsPaused(true);
        OnGameOverEvent.Broadcast();
        GameManager::GetInstance().SetNewGameState(GameState::GameOver);
        diji::ServiceLocator::GetSoundSystem().AddSoundRequest("sound/out_of_time.wav", false);
    }
}

void timber::TimeBar::Reset()
{
    m_RemainingTime = 6.f;
    m_RectRenderCompPtr->GetRectangle().setSize(sf::Vector2f{ 200.f, m_RectRenderCompPtr->GetRectangle().getSize().y });
}

void timber::TimeBar::AddTime(const int score)
{
    if (score)
        m_RemainingTime += 2.f / score + 0.15f;
}
