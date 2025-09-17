#pragma once
#include <string>
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
        explicit Collider(GameObject* ownerPtr, const Rectf& rect);
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

        void SetTag (const std::string& tag) { m_Tag = tag; }
        [[nodiscard]] const std::string& GetTag() const { return m_Tag; }
        [[nodiscard]] Rectf GetCollisionBox() const { return m_CollisionBox; }
        [[nodiscard]] const GameObject* GetParent() const { return GetOwner(); }
        [[nodiscard]] Rectf GetLastState() const { return m_CollisionBox; }
        [[nodiscard]] sf::Vector2f GetOffset() const { return m_Offset; }
        [[nodiscard]] sf::Vector2f GetPosition() const;
        [[nodiscard]] sf::Vector2f GetCenter() const;

    private:
        Transform* m_TransformCompPtr = nullptr;
        sf::Vector2f m_Offset{ 0, 0 };
        std::string m_Tag = "Untagged";
        Rectf m_CollisionBox;
        Rectf m_LastState { .left = 0, .bottom = 0, .width = 0, .height = 0 };
        bool m_IsOffsetSet = false;
        bool m_IsCollisionSet = true;
    };
}

