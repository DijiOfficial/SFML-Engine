#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
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

        void Init() override {}
        void OnEnable() override {}
        void Start() override;
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void RefreshView(bool isSplitscreen) const;

    private:
        diji::Camera* m_CameraCompPtr = nullptr;
        CurrentPlayer m_CurrentCharacter;

        void SetCameraFollow() const;
    };
}
