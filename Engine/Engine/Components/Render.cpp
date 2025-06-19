#include "Render.h"
#include "Transform.h"
// #include "Text.h"
#include "../Core/Renderer.h"
#include "TextureComp.h"
#include "../Core/GameObject.h"
#include <SFML/Graphics/Texture.hpp>

diji::Render::Render(GameObject* ownerPtr, const int scale) 
    : Render(ownerPtr)
{
    m_TextureCompPtr = nullptr;
    m_TransformCompPtr = nullptr;
    m_Scale = scale;
}


diji::Render::Render(GameObject* ownerPtr)
    : Component(ownerPtr)
{
    m_TextureCompPtr = nullptr;
    m_TransformCompPtr = nullptr;
    // m_TextCompPtr = nullptr;
}

void diji::Render::Init()
{
    const auto& ownerPtr = GetOwner();

    m_TransformCompPtr = ownerPtr->GetComponent<Transform>();
    m_TextureCompPtr = ownerPtr->GetComponent<TextureComp>();
    // m_TextCompPtr = ownerPtr->GetComponent<Text>();

    // todo: remove this if fonts behave differently than sdl
    if (m_TextureCompPtr)
        m_SFMLTexture = m_TextureCompPtr->GetTexture();
    else
        throw std::runtime_error("Failed to get texture: m_TextureCompPtr is null in Renderer::UpdateTexture");
    // else
    //     m_TexturePtr = m_TextCompPtr->GetTexture();
}

void diji::Render::RenderFrame() const
{
    if (not m_Render)
        return;

    const sf::Vector2f pos = [this]()
    {
        if (m_TransformCompPtr)
            return m_TransformCompPtr->GetPosition();
        
        return sf::Vector2f{ 0, 0 };
    }();

    if (m_TextureCompPtr)
    {
        if (m_TextureCompPtr->CanRotate())
            Renderer::GetInstance().RenderRotatedTexture(m_SFMLTexture, pos.x, pos.y, m_TextureCompPtr->GetRotationAngle(), m_TextureCompPtr->GetScaleX(), m_TextureCompPtr->GetScaleY());
        else
            Renderer::GetInstance().RenderTexture(m_SFMLTexture, pos.x, pos.y, m_TextureCompPtr->GetScaleX(), m_TextureCompPtr->GetScaleY());
    }
    // else // Text Texture
    //     Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y, m_Scale);

}

// void diji::Render::UpdateText()
// { 
//     m_TexturePtr = m_TextCompPtr->GetTexture(); 
// }

void diji::Render::UpdateTexture(sf::Texture& texture)
{
    m_SFMLTexture = texture;
}
