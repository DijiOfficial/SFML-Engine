#include "Renderer.h"
#include "../Singleton/SceneManager.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Angle.hpp>

void diji::Renderer::Init(sf::RenderWindow* window)
{
	m_WindowPtr = window;
}

void diji::Renderer::Render() const
{
	m_WindowPtr->clear();
	
	SceneManager::GetInstance().Render();

	m_WindowPtr->display();
}

void diji::Renderer::Destroy()
{
	delete m_WindowPtr;
	m_WindowPtr = nullptr;
}

void diji::Renderer::RenderTexture(const sf::Texture& texture, const float x, const float y, const float scaleX, const float scaleY) const
{
	sf::Sprite sprite(texture);
	
	sprite.setPosition(sf::Vector2f{ x, y });
	sprite.setScale(sf::Vector2f{ scaleX, scaleY });

	m_WindowPtr->draw(sprite);
}

void diji::Renderer::RenderTexture(const sf::Texture& texture, const float x, const float y, const float scale) const
{
	RenderTexture(texture, x, y, scale, scale);
}

void diji::Renderer::RenderTexture(const sf::Texture& texture, const float x, const float y, const int width, const int height) const
{
	const sf::Vector2u texSize = texture.getSize();
	const float scaleX = static_cast<float>(width) / texSize.x;
	const float scaleY = static_cast<float>(height) / texSize.y;

	RenderTexture(texture, x, y, scaleX, scaleY);
}

void diji::Renderer::RenderRotatedTexture(const sf::Texture& texture, const float x, const float y, const sf::Angle angle, const float scaleX, const float scaleY) const
{
	sf::Sprite sprite(texture);

	const sf::Vector2u texSize = texture.getSize();
	sprite.setOrigin(sf::Vector2f{ texSize.x * 0.5f, texSize.y * 0.5f});

	sprite.setPosition(sf::Vector2f{ x, y });
	sprite.setRotation(angle);
	sprite.setScale(sf::Vector2f{ scaleX, scaleY });

	m_WindowPtr->draw(sprite);
}

void diji::Renderer::RenderRotatedTexture(const sf::Texture& texture, const float x, const float y, const sf::Angle angle, const float scale) const
{
	RenderRotatedTexture(texture, x, y, angle, scale, scale);
}

void diji::Renderer::RenderRotatedTexture(const sf::Texture& texture, const float x, const float y, const int width, const int height, const sf::Angle angle) const
{
	const sf::Vector2u texSize = texture.getSize();
	const float scaleX = static_cast<float>(width) / texSize.x;
	const float scaleY = static_cast<float>(height) / texSize.y;

	RenderRotatedTexture(texture, x, y, angle, scaleX, scaleY);
}

void diji::Renderer::SetBackgroundColor(const sf::Color& color)
{
	m_ClearColor = color;
}
