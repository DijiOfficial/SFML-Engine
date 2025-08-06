#pragma once
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/View.hpp>

#include "../Components/Component.h"

namespace diji
{
    class Transform;
    class GameObject;

    class Camera final : public Component
    {
    public:
        explicit Camera(GameObject* ownerPtr, float width, float height);
        ~Camera() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}
        
        void SetLevelBoundaries(const sf::FloatRect& levelBoundaries) { m_LevelBoundaries = levelBoundaries; }
        // void Transform(const Rectf& target) const;
        void UnlockCamera() { m_IsLocked = false; }
        void LockCamera() { m_IsLocked = true; }
        void SetOffsetCamera(const int offset) { m_CameraOffset = offset; }
        void ResetOffset() { m_CameraOffset = 0; }
        void SetFollow(const GameObject* target);
        void SetFollowSelf();
        void SetAsMainView() const;
        
        int GetCameraOffset() const { return m_CameraOffset; }
        bool GetIsCameraLocked() const { return m_IsLocked; }
        sf::Vector2i GetMouseWorldPosition(const sf::Vector2i& pos) const;
        // Rectf GetCameraView(const Rectf& target) const {return }???
        
    private:
        Transform* m_TransformCompPtr = nullptr;
        sf::View m_CameraView;
        sf::FloatRect m_LevelBoundaries;
        float m_Width;
        float m_Height;
        int m_CameraOffset;
        bool m_IsLocked;

        // sf::Vector2f Track(const Rectf& target) const;
        // void Clamp(sf::Vector2f& bottomLeftPos) const;
    };
}
