#pragma once
#include "Engine/Input/GameActorCommand.h"

namespace timber
{
    class Restart final : public diji::GameActorCommands
    {
    public:
        explicit Restart(diji::GameObject* actor) : GameActorCommands{ actor } {}
        ~Restart() noexcept override = default;

        void Execute() override;
    };

    class MovePlayer final : public diji::GameActorCommands
    {
    public:
        enum class Direction
        {
            Left,
            Right
        };
        
        explicit MovePlayer(diji::GameObject* actor, Direction dir);
        ~MovePlayer() noexcept override = default;
        
        void Execute() override;
        
    private:
        Direction m_Direction;
    };

    class Pause final : public diji::GameActorCommands
    {
    public:
        explicit Pause(diji::GameObject* actor) : GameActorCommands{ actor } {}
        ~Pause() noexcept override = default;

        void Execute() override;
    };

}
