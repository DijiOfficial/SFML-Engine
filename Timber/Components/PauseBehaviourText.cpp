#include "PauseBehaviourText.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Render.h"
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

void timber::PauseBehaviourText::OnGameOver()
{
    GetOwner()->GetComponent<diji::TextComp>()->GetText().setString("Out of time!!");
    RefreshDisplay();
}

void timber::PauseBehaviourText::Reset()
{
    GetOwner()->GetComponent<diji::TextComp>()->GetText().setString("Press Enter to start!");
    diji::PauseSingleton::GetInstance().SetIsPaused(false);

    RefreshDisplay();
}

void timber::PauseBehaviourText::RefreshDisplay()
{
    m_IsPaused = diji::PauseSingleton::GetInstance().GetIsPaused();
    
    if (m_IsPaused)
        m_RenderCompPtr->EnableRender();
    else
        m_RenderCompPtr->DisableRender();
}

void timber::PauseBehaviourText::OnSquished()
{
    GetOwner()->GetComponent<diji::TextComp>()->GetText().setString("SQUISHED!!");
    RefreshDisplay();
}
