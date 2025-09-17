#pragma once
#include <SFML/System/Vector2.hpp>

#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
    class Camera;
    class Collider;
}

namespace thomasWasLate
{
    enum class CurrentPlayer;

    class PlayerCharacter : public diji::Component
    {
    public:
        explicit PlayerCharacter(diji::GameObject* ownerPtr, CurrentPlayer currPlayer);
        ~PlayerCharacter() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override;
        
        void Update() override {}
        void FixedUpdate() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void RefreshView(bool isSplitscreen) const;
        void Move(const sf::Vector2f& direction) const;

    protected:
        float m_Speed = 400.f;
        
    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::Camera* m_CameraCompPtr = nullptr;
        diji::Collider* m_ColliderCompPtr = nullptr;
        CurrentPlayer m_CurrentCharacter;
        const float GRAVITY = 300.f;
        bool m_IsOnGround = false;

        void SetCameraFollow() const;
        void RefreshView() const { RefreshView(false); }
    };
}
