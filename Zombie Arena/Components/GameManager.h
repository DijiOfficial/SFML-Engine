#pragma once
#include <memory>
#include <SFML/Graphics/Rect.hpp>

#include "Engine/Singleton/Singleton.h"
#include "Engine/Interfaces/EventSystem.h"
#include "Engine/Core/GameObject.h"

//todo: add zombie counter and scene changes
// todo: increase core when zombie dies
namespace zombieArena
{
    enum class PickUpType;
    
    class GameManager final : public diji::Singleton<GameManager>
    {
    public:
        void Init();
        diji::Event<PickUpType, int> OnPickedUpEvent;
        diji::Event<> OnZombieKilledEvent;

        [[nodiscard]] int GetCurrentWave() const { return m_CurrentWave; }
    private:
        std::unique_ptr<diji::GameObject> m_AmmoPickUpTemplate = nullptr;
        std::unique_ptr<diji::GameObject> m_HealthPickUpTemplate = nullptr;
        sf::IntRect m_InnerArenaRect;

        int m_CurrentWave = 1;
        float m_AmmoTimerRespawn = 10.f;
        float m_HealthTimerRespawn = 10.f;

        void RespawnPickUp(PickUpType type, int) const;
    };
}
