#pragma once
#include "Singleton.h"
// #include "Font.h"
// #include "SoundEffect.h"
// #include "Music.h"

#include <string>
// #include <memory>
#include <unordered_map>

namespace sf
{
    class Texture;
}

namespace diji
{
    class ResourceManager final : public Singleton<ResourceManager>
    {
    public:
        void Init(const std::string& dataPath);
        sf::Texture& LoadTexture(const std::string& file);
        // Font* LoadFont(const std::string& file, unsigned int size);
        // SoundEffect* LoadSoundEffect(const std::string& file);
        // Music* LoadMusic(const std::string& file);

    private:
        std::string m_DataPath;

        std::unordered_map<std::string, sf::Texture> m_TexturesUPtrUMap;
        // std::unordered_multimap<std::string, std::pair<unsigned int, std::unique_ptr<Font>>> m_FontsUPtrUMap;
        //
        // std::unordered_map<std::string, std::unique_ptr<SoundEffect>> m_SoundEffectsUPtrUMap;
        // std::unordered_map<std::string, std::unique_ptr<Music>> m_MusicUPtrUMap;
    };
}
