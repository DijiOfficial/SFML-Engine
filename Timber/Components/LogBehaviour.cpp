#include "LogBehaviour.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "engine/Singleton/TimeSingleton.h"

void timber::LogBehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
}

void timber::LogBehaviour::Update()
{
    if (!m_IsActive)
        return;

    const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime();
    m_TransformCompPtr->AddOffset(m_Speed * dt);
    
    const float posX = m_TransformCompPtr->GetPosition().x;
    if (posX < -100 || posX > 2000)
    {
        m_IsActive = false;
        m_TransformCompPtr->SetPosition(810, 720);
    }
}

void timber::LogBehaviour::Activate(const bool isLeft)
{
    m_TransformCompPtr->SetPosition(810,720);
    m_Speed = { isLeft ? 5000.f : -5000.f,  -1500.f };
    m_IsActive = true;
}
