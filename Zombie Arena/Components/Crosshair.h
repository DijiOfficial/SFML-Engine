#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
    class Camera;
}

namespace zombieArena
{
    class Crosshair final : public diji::Component
    {
    public:
        explicit Crosshair(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~Crosshair() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::Camera* m_CameraCompPtr = nullptr;
    };
}
