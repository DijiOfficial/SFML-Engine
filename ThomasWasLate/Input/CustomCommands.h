#pragma once
#include "Engine/Input/GameActorCommand.h"

namespace thomasWasLate
{
    class PlayerCharacter;

    class SwitchSplitScreenView final : public diji::GameActorCommands
    {
    public:
        explicit SwitchSplitScreenView(diji::GameObject* actor, PlayerCharacter* thomas, PlayerCharacter* bob);
        ~SwitchSplitScreenView() noexcept override = default;

        void Execute() override;
        
    private :
        bool m_IsMultiplayer = false;
        PlayerCharacter* m_Thomas = nullptr;
        PlayerCharacter* m_Bob = nullptr;
    };
}
