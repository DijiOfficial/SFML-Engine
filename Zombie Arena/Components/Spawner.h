#pragma once
#include "Engine/Components/Component.h"

#include <memory>
#include <SFML/Graphics/Rect.hpp>

namespace zombieArena
{
    class Spawner final : public diji::Component
    {
    public:
        // pass the player
        explicit Spawner(diji::GameObject* ownerPtr, diji::GameObject* playerPtr, const sf::IntRect& arena);
        ~Spawner() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void CreateHorde(const int totalZombies) const;

        diji::Event<int> OnWaveSpawnedEvent;

    private:
        diji::GameObject* m_PlayerPtr = nullptr;
        std::unique_ptr<diji::GameObject> m_ZombieTemplatePtr = nullptr;
        sf::IntRect m_Arena;
        
        const int ZOMBIE_PER_WAVE = 5;
    };
}
