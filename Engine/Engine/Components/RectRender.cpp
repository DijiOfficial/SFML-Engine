#include "RectRender.h"
#include "../Core/Renderer.h"
#include "Transform.h"
#include "../Core/GameObject.h"

void diji::RectRender::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<Transform>();
}

void diji::RectRender::RenderFrame() const
{
    if (not m_Render)
        return;

    m_RectangleShape.setPosition(m_TransformCompPtr->GetPosition());

    Renderer::GetInstance().DrawRect(m_RectangleShape, m_OutlineColor, m_FillColor, m_LineWidth);
}
