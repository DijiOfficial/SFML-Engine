#include "TextureComp.h"

#include "Render.h"
#include "../Singleton/ResourceManager.h"
#include "../Core/GameObject.h"

diji::TextureComp::TextureComp(GameObject* ownerPtr)
	: Component(ownerPtr)
{
}

diji::TextureComp::TextureComp(GameObject* ownerPtr, std::string filename)
	: Component(ownerPtr)
	, m_FilePath{std::move(filename)}
{
}

diji::TextureComp::TextureComp(GameObject* ownerPtr, std::string filename, const float scaleX, const float scaleY)
	: Component(ownerPtr)
	, m_FilePath{ std::move(filename) }
	, m_ScaleX{ scaleX }
	, m_ScaleY{ scaleY }
{
}

diji::TextureComp::TextureComp(GameObject* ownerPtr, std::string filename, const float scale)
	: Component(ownerPtr)
	, m_FilePath{ std::move(filename) }
	, m_ScaleX{ scale }
	, m_ScaleY{ scale }
{
}

void diji::TextureComp::Init()
{
	if (not m_FilePath.empty())
		SetTexture(m_FilePath);
	// else console log warning path not set or something
}

void diji::TextureComp::SetTexture(const std::string& filename)
{
	m_SFMLTexture = ResourceManager::GetInstance().LoadTexture(filename);
	if (GetOwner()->HasComponent<Render>())
		GetOwner()->GetComponent<Render>()->UpdateTexture(m_SFMLTexture);
}

void diji::TextureComp::SetScaleX(const float scaleX)
{
	m_ScaleX = scaleX;
}

void diji::TextureComp::SetScaleY(const float scaleY)
{
	m_ScaleY = scaleY;
}

void diji::TextureComp::SetScale(const float scale)
{
	m_ScaleX = scale;
	m_ScaleY = scale;
}

void diji::TextureComp::SetWidth(const int width)
{
	SetScaleX(static_cast<float>(width) / m_SFMLTexture.getSize().x);
}

void diji::TextureComp::SetHeight(const int height)
{
	SetScaleY(static_cast<float>(height) / m_SFMLTexture.getSize().y);
}

// todo: consider whether I should use float for sizes?
int diji::TextureComp::GetWidth() const
{
	return static_cast<int>(m_SFMLTexture.getSize().x * m_ScaleX);
}

int diji::TextureComp::GetHeight() const
{
	return static_cast<int>(m_SFMLTexture.getSize().y * m_ScaleY);
}
