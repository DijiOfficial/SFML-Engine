#include "TimeBar.h"

#include "../Interfaces/Observers.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/RectRender.h"
#include "Engine/Singleton/PauseSingleton.h"

void timber::TimeBar::Init()
{
    m_RectRenderCompPtr = GetOwner()->GetComponent<diji::RectRender>();
}

void timber::TimeBar::Update()
{
    m_RemainingTime -= diji::TimeSingleton::GetInstance().GetDeltaTime(); // optimize this call?

    m_RectRenderCompPtr->GetRectangle().setSize(sf::Vector2f{ m_WidthPerSecond * m_RemainingTime, m_RectRenderCompPtr->GetRectangle().getSize().y});

    if (m_RemainingTime <= 0.0f)
    {
        diji::PauseSingleton::GetInstance().SetIsPaused(true);
        Notify(static_cast<diji::MessageTypes>(MessageTypesDerived::GameOver));
    }
}
