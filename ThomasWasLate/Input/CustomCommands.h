#pragma once
#include "Engine/Input/GameActorCommand.h"

namespace thomasWasLate
{
    class SwitchSplitScreenView final : public diji::GameActorCommands
    {
    public:
        explicit SwitchSplitScreenView(diji::GameObject* actor) : GameActorCommands{ actor } {}
        ~SwitchSplitScreenView() noexcept override = default;

        void Execute() override;
        
    private :
        bool m_IsMultiplayer = false;
    };
}
