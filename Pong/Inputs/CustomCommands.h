#pragma once
#include "Engine/Input/GameActorCommand.h"

namespace pong
{
    enum class Movement
    {
        Left,
        Right,
    };
    
    class MovePlayer final : public diji::GameActorCommands
    {
    public:
        
        explicit MovePlayer(diji::GameObject* actor, Movement movement, bool isStart);
        ~MovePlayer() noexcept override = default;
        
        void Execute() override;

    private:
        Movement m_Movement;
        bool m_IsStart;
    };
}
