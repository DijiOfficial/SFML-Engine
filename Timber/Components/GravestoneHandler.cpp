#include "GravestoneBehaviour.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"

void timber::GravestoneBehaviour::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    m_RenderCompPtr = GetOwner()->GetComponent<diji::Render>();
}

void timber::GravestoneBehaviour::Move(const bool isLeft)
{
    m_PosX = isLeft ? 525.f : 1200.f;
}

void timber::GravestoneBehaviour::Enable()
{
    m_RenderCompPtr->EnableRender();
    m_TransformCompPtr->SetPosition(m_PosX, 760);
}

void timber::GravestoneBehaviour::Reset()
{
    m_RenderCompPtr->DisableRender();
}
