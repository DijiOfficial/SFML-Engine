#pragma once
#include "../../3rdParty/SFML_x64/include/SFML/Window/Context.hpp"
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

}
