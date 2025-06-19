#include "ResourceManager.h"

#include <stdexcept>
#include <SFML/Graphics/Texture.hpp>


void diji::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// if (TTF_Init() != 0)
	// {
	// 	throw std::runtime_error(std::string("Failed to load support for fonts: "));
	// }
}

sf::Texture& diji::ResourceManager::LoadTexture(const std::string& file)
{
	// check if texture is already loaded
	const auto fullPath = m_DataPath + file;
	const auto it = m_TexturesUPtrUMap.find(fullPath);
	if (it != m_TexturesUPtrUMap.cend())
	{
		return it->second;
	}

	// if not cache it
	sf::Texture tempTexture;
	if (!tempTexture.loadFromFile(fullPath.c_str()))
	{
		throw std::runtime_error("Failed to load texture: " + fullPath);
	}

	m_TexturesUPtrUMap[fullPath] = sf::Texture(tempTexture);
	return m_TexturesUPtrUMap[fullPath];
}
