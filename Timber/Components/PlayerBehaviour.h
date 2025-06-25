#pragma once
#include "Engine/Components/Component.h"


namespace timber 
{
    enum class BranchSide;

    class PlayerBehaviour final : public diji::Component
    {
    public:
        explicit PlayerBehaviour(diji::GameObject* ownerPtr);
        ~PlayerBehaviour() noexcept override = default;

        void Init() override {}
        void OnEnable() override {}
        void Start() override {}
		
        void FixedUpdate() override {}
        void Update() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void Restart();
        
    private:
        BranchSide m_PlayerSide;
        
    };
}
