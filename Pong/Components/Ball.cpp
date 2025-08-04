#include "Ball.h"

#include "Engine/Components/RectRender.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/Transform.h"

namespace // todo: remove this and use the window singleton
{
    constexpr static sf::Vector2u VIEWPORT{ 1920, 1080 };
}


void pong::Ball::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();

    m_Size = static_cast<int>(GetOwner()->GetComponent<diji::RectRender>()->GetRectangle().getSize().x);
}

void pong::Ball::Update()
{
    const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime(); // consider using static instance member
    
    m_TransformCompPtr->AddOffset(m_Velocity * dt * m_Speed);

    const auto& pos = m_TransformCompPtr->GetPosition();
    if (pos.y > VIEWPORT.y)
    {
        ResetBall();

        if (!m_DirtyFlagUpdate)
            OnLifeLostEvent.Broadcast();

        m_DirtyFlagUpdate = true;

        return; // early return, player lost no need to update rest of the frame
    }

    if (pos.y < 0) // top of the screen bounce
    {
        m_Velocity.y = abs(m_Velocity.y);
        OnIncreaseScoreEvent.Broadcast();
    }

    if (pos.x < 0 || pos.x + m_Size > VIEWPORT.x) // bouncing side of screen
        m_Velocity.x = -m_Velocity.x;

    // if (GetOwner()->GetComponent<diji::RectRender>()->GetRectangle().getGlobalBounds().contains())
    // {
    //     // Hit detected so reverse the ball and score a point
    //     ball.reboundBatOrTop();
    // }
}

void pong::Ball::ResetBall()
{
    m_TransformCompPtr->SetPosition(VIEWPORT.x * 0.5f, 0);
    m_Velocity.y = abs(m_Velocity.y);
    m_DirtyFlagUpdate = false;
}

