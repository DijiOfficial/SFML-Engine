#include "Beehaviour.h"

#include "Engine/Components/Transform.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Singleton/TimeSingleton.h"

void timber::Beehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
}

void timber::Beehaviour::Start()
{
    Randomize();
}

void timber::Beehaviour::Update()
{
    // could optimise the calls to the singletons
    m_TransformCompPtr->AddOffset(-m_Speed * diji::TimeSingleton::GetInstance().GetDeltaTime(), 0);

    if (m_TransformCompPtr->GetPosition().x < -100)
    {
        Randomize();
    }
}

void timber::Beehaviour::Randomize()
{
    const auto& rand = diji::RandNumber::GetInstance();
    m_Speed = rand.GetRandomRangeFloat(200, 400);
    
    m_TransformCompPtr->SetPosition(2000, rand.GetRandomRangeFloat(500, 1000));
}
