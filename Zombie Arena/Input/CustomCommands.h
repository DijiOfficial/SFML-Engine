#pragma once
#include <SFML/System/Vector2.hpp>

#include "Engine/Input/GameActorCommand.h"

namespace zombieArena
{
    enum class ZombieGameState;
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

    class Reload final : public diji::GameActorCommands
    {
    public:
        explicit Reload(diji::GameObject* actor);
        ~Reload() noexcept override = default;

        void Execute() override;

    private:
        Player* m_PlayerCompPtr = nullptr;
    };

    class Start final : public diji::GameActorCommands
    {
    public:
        explicit Start(diji::GameObject* actor, ZombieGameState nextState);
        ~Start() noexcept override = default;

        void Execute() override;
    private:
        ZombieGameState m_NextState;
    };

    enum class UpgradeType;
    class UpgradeChoice final : public diji::GameActorCommands
    {
    public:
        explicit UpgradeChoice(diji::GameObject* actor, UpgradeType upgradeType);
        ~UpgradeChoice() noexcept override = default;

        void Execute() override;
    private:
        UpgradeType m_UpgradeType;
    };
}
