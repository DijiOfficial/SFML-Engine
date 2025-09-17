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

    class PlayerCharacter final : public diji::Component
    {
    public:
        explicit PlayerCharacter(diji::GameObject* ownerPtr, CurrentPlayer currPlayer, float jumpTime);
        ~PlayerCharacter() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override;
        
        void Update() override;
        void FixedUpdate() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void RefreshView(bool isSplitscreen) const;
        void Move(const sf::Vector2f& direction) const;

        void Jump(bool ignoreTimer = false);
        void ClearJump();

    protected:
        float m_Speed = 400.f;
    private:
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::Camera* m_CameraCompPtr = nullptr;
        diji::Collider* m_ColliderCompPtr = nullptr;
        sf::Vector2f m_SpawnPoint = { 0.f, 0.f };
        CurrentPlayer m_CurrentCharacter;
        bool m_IsOnGround = false;
        bool m_IsJumping = false;
        bool m_IsBoosting = false;
        const float GRAVITY = 300.f;
        float m_JumpTime = 0.0f;
        float m_MaxJumpTime = 0.25f;

        void SetCameraFollow() const;
        void RefreshView() const { RefreshView(false); }

        void OnNewLevelLoaded();

        void CheckForBoosting();
    };
}
