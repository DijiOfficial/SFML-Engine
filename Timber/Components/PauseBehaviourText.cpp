#include "PauseBehaviourText.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Render.h"
#include "../Interfaces/Observers.h"
#include "Engine/Components/TextComp.h"

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
    }


    
    m_IsPaused = !m_IsPaused;
    
    if (m_IsPaused)
        m_RenderCompPtr->EnableRender();
    else
        m_RenderCompPtr->DisableRender();

}
