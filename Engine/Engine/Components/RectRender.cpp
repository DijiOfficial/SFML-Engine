#include "RectRender.h"
#include "../Core/Renderer.h"

void diji::RectRender::RenderFrame() const
{
    if (not m_Render)
        return;

    Renderer::GetInstance().DrawRect(m_RectangleShape, m_OutlineColor, m_FillColor, m_LineWidth);
}
