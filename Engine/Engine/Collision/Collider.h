#pragma once
#include <SFML/System/Vector2.hpp>

#include "../Components/Component.h"
#include "CollisionSingleton.h"

namespace diji 
{
    class Transform;
    class Collider final : public Component
    {
    public:
        explicit Collider(GameObject* ownerPtr);
        explicit Collider(GameObject* ownerPtr, const float width, const float height);
        explicit Collider(GameObject* ownerPtr, const int width, const int height);
        explicit Collider(GameObject* ownerPtr, const int width, const int height, const sf::Vector2f& offset);
        ~Collider() noexcept override = default;

        void Init() override {}
        void OnEnable() override {}
        void Start() override;

        void FixedUpdate() override {}
        void Update() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override;

        void UpdateColliderFromTexture();

        [[nodiscard]] Rectf GetCollisionBox() const { return m_CollisionBox; } // todo: const ref?
        [[nodiscard]] const GameObject* GetParent() const { return GetOwner(); }
        [[nodiscard]] Rectf GetLastState() const { return m_CollisionBox; }
        [[nodiscard]] sf::Vector2f GetOffset() const { return m_Offset; }
        [[nodiscard]] sf::Vector2f GetPosition() const;

    private:
        sf::Vector2f m_Offset{ 0, 0 };
        Transform* m_TransformCompPtr = nullptr;
        Rectf m_CollisionBox;
        Rectf m_LastState { .left = 0, .bottom = 0, .width = 0, .height = 0 };
        bool m_IsOffsetSet = false;
        bool m_IsCollisionSet = true;
    };
}

