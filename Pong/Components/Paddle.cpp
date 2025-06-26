#include "Paddle.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/Transform.h"

void pong::Paddle::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
}

void pong::Paddle::Update()
{
    if (m_IsMovingLeft == m_IsMovingRight)
        return;
    
    const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime();
    
    m_TransformCompPtr->AddOffset(m_IsMovingLeft ? m_Speed * -dt : m_Speed * dt, 0);
}
