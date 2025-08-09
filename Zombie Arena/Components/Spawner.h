#pragma once
#include <memory>

#include "Engine/Components/Component.h"

namespace zombieArena
{
    class Spawner final : public diji::Component
    {
    public:
        // pass the player
        explicit Spawner(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Spawner() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

    private:
        std::unique_ptr<diji::GameObject> m_ZombieTemplatePtr = nullptr;
    };
}
