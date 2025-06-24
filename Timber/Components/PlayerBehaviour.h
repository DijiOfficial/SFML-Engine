#pragma once
#include "Engine/Components/Component.h"

namespace timber 
{
    class PlayerBehaviour final : public diji::Component
    {
    public:
        explicit PlayerBehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
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
        
    };
}
