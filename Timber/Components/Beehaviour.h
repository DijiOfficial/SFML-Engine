#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
}

namespace timber 
{
    class Beehaviour final : public diji::Component
    {
    public:
        Beehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Beehaviour() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override;
		
        void FixedUpdate() override {}
        void Update() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}
		
    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        float m_Speed = 0.f;

        void Randomize();
    };
}
