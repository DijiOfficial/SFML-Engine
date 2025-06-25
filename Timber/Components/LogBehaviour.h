#pragma once
#include "Engine/Components/Component.h"
#include <SFML/System/Vector2.hpp>

namespace sf
{
    template <typename T> class Vector2;
    using Vector2f = Vector2<float>;
}

namespace timber
{    
    class LogBehaviour final : public diji::Component
    {
    public:
        explicit LogBehaviour(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        ~LogBehaviour() noexcept override = default;

        void Init() override {}
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

    private:
        sf::Vector2f m_Speed = { 0.f, 0.f };
        bool m_IsActive = false;
    };
}


