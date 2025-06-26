#include "LogBehaviour.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "engine/Singleton/TimeSingleton.h"
#include "Engine/Components/TextureComp.h"

void timber::LogBehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_Origin = m_TransformCompPtr->GetPosition().y;
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();
    m_TextureCompPtr->SetOrigin( m_TextureCompPtr->GetWidth() * 0.5f, m_TextureCompPtr->GetHeight() * 0.5f);
}

void timber::LogBehaviour::Update()
{
    if (!m_IsActive)
        return;

    const float dt = diji::TimeSingleton::GetInstance().GetDeltaTime();
    m_TransformCompPtr->AddOffset(m_Speed * dt);
    m_RotationAngle += m_Speed.y * dt * 1.5f;
    m_TextureCompPtr->SetRotationAngle(m_RotationAngle);
    
    const float posX = m_TransformCompPtr->GetPosition().x;
    if (posX < -100 || posX > 2000)
    {
        m_IsActive = false;
        m_TransformCompPtr->SetPosition(960, m_Origin);
        m_TextureCompPtr->SetRotationAngle(0.f);
        m_RotationAngle = 0.f;
    }
}

void timber::LogBehaviour::Activate(const bool isLeft)
{
    m_TransformCompPtr->SetPosition(960,m_Origin);
    m_Speed = { isLeft ? 5000.f : -5000.f,  -1500.f };
    m_IsActive = true;
}
