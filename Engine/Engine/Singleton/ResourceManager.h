#pragma once
#include "Singleton.h"
// #include "Font.h"
// #include "SoundEffect.h"
// #include "Music.h"

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <unordered_map>

namespace sf
{
    class Texture;
    class Font;
}

namespace diji
{
    class ResourceManager final : public Singleton<ResourceManager>
    {
    public:
        void Init(const std::string& dataPath);
        [[nodiscard]] sf::Texture& LoadTexture(const std::string& file);
        [[nodiscard]] sf::Font& LoadFont(const std::string& file);
        // SoundEffect* LoadSoundEffect(const std::string& file);
        // Music* LoadMusic(const std::string& file);

    private:
        std::string m_DataPath;

        std::unordered_map<std::string, sf::Texture> m_TexturesUMap;
        std::unordered_map<std::string, sf::Font> m_FontsUMap;
        
        // std::unordered_map<std::string, std::unique_ptr<SoundEffect>> m_SoundEffectsUPtrUMap;
        // std::unordered_map<std::string, std::unique_ptr<Music>> m_MusicUPtrUMap;
    };
}
