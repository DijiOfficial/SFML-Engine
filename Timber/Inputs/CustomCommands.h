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

    private:
    };

}
