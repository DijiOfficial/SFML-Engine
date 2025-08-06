#include "Ball.h"

#include "Engine/Collision/Collider.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Components/RectRender.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/Engine.h"
#include "engine/Singleton/SceneManager.h"
#include "Engine/Singleton/TimerManager.h"

void pong::Ball::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();

    m_Size = static_cast<int>(GetOwner()->GetComponent<diji::RectRender>()->GetRectangle().getSize().x);

    m_ColliderCompPtr = GetOwner()->GetComponent<diji::Collider>();
    m_PaddleColliderCompPtr = diji::SceneManager::GetInstance().GetGameObject("A_Paddle")->GetComponent<diji::Collider>();

    m_CollisionSingleton = &diji::CollisionSingleton::GetInstance();
}

void pong::Ball::Update()
{
    const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime(); // consider using static instance member
    
    m_TransformCompPtr->AddOffset(m_Velocity * dt * m_Speed);

    const auto& pos = m_TransformCompPtr->GetPosition();
    if (pos.y > window::VIEWPORT.y)
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
    }

    if (pos.x < 0 || pos.x + m_Size > window::VIEWPORT.x) // bouncing side of screen
        m_Velocity.x = -m_Velocity.x;
    
    if (!m_DirtyFlagCollision and m_CollisionSingleton->AreColliding(m_ColliderCompPtr, m_PaddleColliderCompPtr))
    {
        m_DirtyFlagCollision = true;

        CalculateNewVelocity();

        OnIncreaseScoreEvent.Broadcast();
        if (m_Speed < m_OriginalSpeed * 5.f)
            m_Speed *= 1.1f;

        (void)diji::TimerManager::GetInstance().SetTimer([this]() { m_DirtyFlagCollision = false; }, 0.05f, false);
    }
}

void pong::Ball::ResetBall()
{
    m_TransformCompPtr->SetPosition(window::VIEWPORT.x * 0.5f, 0);
    m_Velocity.y = abs(m_Velocity.y);
    m_DirtyFlagUpdate = false;
}

void pong::Ball::CalculateNewVelocity()
{
    // Get the positions of the ball and paddle
    const auto& ballPos = m_TransformCompPtr->GetPosition();
    const auto& paddlePos = m_PaddleColliderCompPtr->GetParent()->GetComponent<diji::Transform>()->GetPosition();

    // Calculate the direction vector from the paddle to the ball
    sf::Vector2f direction = ballPos - paddlePos;

    // Normalize the direction vector
    const float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (magnitude > 0.0f)
        direction /= magnitude;

    // Clamp the x and y components of the direction vector
    direction.x = std::clamp(direction.x, -0.9f, 0.9f);
    direction.y = std::clamp(direction.y, -0.9f, -0.1f);

    // Ensure values are not between -0.1 and 0.1
    if (direction.x > -0.1f && direction.x < 0.1f)
        direction.x = (direction.x < 0.0f) ? -0.1f : 0.1f;

    // Apply the new velocity
    m_Velocity = direction;
}
