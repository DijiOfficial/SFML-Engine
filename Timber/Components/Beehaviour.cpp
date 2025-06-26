#include "Beehaviour.h"

#include "Engine/Components/Transform.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Singleton/TimeSingleton.h"
#include "Engine/Components/TextureComp.h"

void timber::Beehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();
}

void timber::Beehaviour::Start()
{
    Randomize();
}

void timber::Beehaviour::Update()
{
    // could optimise the calls to the singletons
    m_TransformCompPtr->AddOffset(m_SpeedModifier * m_Speed * diji::TimeSingleton::GetInstance().GetDeltaTime(), 0);

    if (m_TransformCompPtr->GetPosition().x < -205 or m_TransformCompPtr->GetPosition().x > 2005)
    {
        Randomize();
    }
}

void timber::Beehaviour::Randomize()
{
    const auto& rand = diji::RandNumber::GetInstance();
    m_Speed = rand.GetRandomRangeFloat(m_MinSpeed, m_MaxSpeed);

    if (m_ClassType == ClassType::Bee)
    {
        const bool isLeft = rand.GetRandomRangeInt(0, 1);
        m_SpeedModifier = isLeft ? -1 : 1;
        m_StartPosition = isLeft ? 2000.f : -200.f;
        const float size = rand.GetRandomRangeFloat(m_MinSize, 1.f);
        m_TextureCompPtr->SetScale(size);
        m_TextureCompPtr->SetScaleX(isLeft ? size : -1.f * size);
    }
    
    m_TransformCompPtr->SetPosition(m_StartPosition, rand.GetRandomRangeFloat(m_MinHeight, m_MaxHeight));

    if (m_ClassType != ClassType::Bee)
        m_TextureCompPtr->SetScale(rand.GetRandomRangeFloat(m_MinSize, 1.f));
}
