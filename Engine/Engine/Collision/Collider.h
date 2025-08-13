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
        void OnDestroy() override {}

        [[nodiscard]] Rectf GetCollisionBox() const { return m_CollisionBox; } // todo: const ref?
        [[nodiscard]] const GameObject* GetParent() const { return GetOwner(); }

    private:
        sf::Vector2f m_Offset{ 0, 0 };
        Transform* m_TransformCompPtr = nullptr;
        Rectf m_CollisionBox;
        bool m_IsOffsetSet = false;
        bool m_IsCollisionSet = true;
    };
}

