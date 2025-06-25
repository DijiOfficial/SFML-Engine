#include "PauseBehaviourText.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Render.h"
#include "../Interfaces/Observers.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Singleton/PauseSingleton.h"

timber::PauseBehaviourText::PauseBehaviourText(diji::GameObject* ownerPtr)
    : Component(ownerPtr)
    , m_RenderCompPtr{ nullptr }
{
    
}

void timber::PauseBehaviourText::Init()
{
    m_RenderCompPtr = GetOwner()->GetComponent<diji::Render>();
}

void timber::PauseBehaviourText::OnNotify(const diji::MessageTypes message)
{
    switch (static_cast<MessageTypesDerived>(message))
    {
    case MessageTypesDerived::GameOver:
        GetOwner()->GetComponent<diji::TextComp>()->GetText().setString("Out of time!!");

        break;
    case MessageTypesDerived::ScoreChange:
        break;
    case MessageTypesDerived::Restart:
        GetOwner()->GetComponent<diji::TextComp>()->GetText().setString("Press Enter to start!");
        diji::PauseSingleton::GetInstance().SetIsPaused(false);
        break;
    default:
        break;
    }


    
    m_IsPaused = diji::PauseSingleton::GetInstance().GetIsPaused();
    
    if (m_IsPaused)
        m_RenderCompPtr->EnableRender();
    else
        m_RenderCompPtr->DisableRender();

}
