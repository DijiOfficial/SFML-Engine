#pragma once
#include <SFML/System/Vector2.hpp>

#include "Engine/Input/GameActorCommand.h"

namespace zombieArena
{
    class Player;

    enum class Movement
    {
        Left,
        Right,
        Top,
        Bottom,
    };
    
    class MovePlayer final : public diji::GameActorCommands
    {
    public:
        explicit MovePlayer(diji::GameObject* actor, Movement movement, bool isStart);
        ~MovePlayer() noexcept override = default;
        
        void Execute() override;

    private:
        Player* m_PlayerCompPtr = nullptr;
        sf::Vector2f m_Direction = {0, 0};
        bool m_IsStart;
    };

    class Aim final : public diji::GameActorCommands
    {
    public:
        explicit Aim(diji::GameObject* actor);
        ~Aim() noexcept override = default;

        void Execute() override {}
        void Execute(const sf::Vector2i& mousePos) override;

    private:
        Player* m_PlayerCompPtr = nullptr;
    };

    class Pause final : public diji::GameActorCommands
    {
    public:
        using GameActorCommands::GameActorCommands;
        ~Pause() noexcept override = default;

        void Execute() override;
    };

    class Shoot final : public diji::GameActorCommands
    {
    public:
        explicit Shoot(diji::GameObject* actor, bool isStart);
        ~Shoot() noexcept override = default;

        void Execute() override;

    private:
        Player* m_PlayerCompPtr = nullptr;
        bool m_IsStart = false;
    };
}
