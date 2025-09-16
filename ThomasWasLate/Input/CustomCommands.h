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

    class MoveCharacter final : public diji::GameActorCommands
    {
    public:
        explicit MoveCharacter(diji::GameObject* actor, const sf::Vector2f& direction);
        ~MoveCharacter() noexcept override = default;

        void Execute() override;

    private:
        const sf::Vector2f m_Direction;
        PlayerCharacter* m_Character = nullptr;
    };
}
