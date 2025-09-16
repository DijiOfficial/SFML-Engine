#pragma once
#include <SFML/System/Vector2.hpp>

#include "Engine/Components/Component.h"

namespace diji
{
    class Transform;
    class Camera;
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
        void FixedUpdate() override {}
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
        CurrentPlayer m_CurrentCharacter;

        void SetCameraFollow() const;
    };
}
