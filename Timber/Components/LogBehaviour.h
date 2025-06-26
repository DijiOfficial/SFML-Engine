#pragma once
#include "Engine/Components/Component.h"
#include <SFML/System/Vector2.hpp>

namespace diji
{
    class TextureComp;
}

namespace diji
{
    class Transform;
}

namespace timber
{    
    class LogBehaviour final : public diji::Component
    {
    public:
        explicit LogBehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~LogBehaviour() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void Activate(bool isLeft = false);

    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::TextureComp* m_TextureCompPtr = nullptr;
        sf::Vector2f m_Speed = { 0.f, 0.f };
        bool m_IsActive = false;
        float m_Origin = 0.f;
        float m_RotationAngle = 0.f;
    };
}


