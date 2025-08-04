#include "Collider.h"
#include "../Components/Transform.h"
#include "../Core/GameObject.h"

diji::Collider::Collider(GameObject* ownerPtr, const int width, const int height)
    : Component(ownerPtr)
{
    m_TransformCompPtr = nullptr;
    m_CollisionBox = { .left = 0, .bottom = 0, .width = static_cast<float>(width), .height = static_cast<float>(height) };
}

diji::Collider::Collider(GameObject* ownerPtr, const int width, const int height, const sf::Vector2f& offset)
    : Component(ownerPtr)
    , m_IsOffsetSet{ true }
    , m_Offset{ offset }
{
    m_TransformCompPtr = nullptr;
    m_CollisionBox = { .left = 0, .bottom = 0, .width = static_cast<float>(width), .height = static_cast<float>(height) };
}

diji::Collider::Collider(GameObject* ownerPtr, const float width, const float height)
    : Component(ownerPtr)
{
    m_TransformCompPtr = nullptr;
    m_CollisionBox = { .left = 0, .bottom = 0, .width = width, .height = height };
}

void diji::Collider::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<Transform>();

    const auto& pos = m_TransformCompPtr->GetPosition();
    m_CollisionBox.left = pos.x + m_Offset.x;
    m_CollisionBox.bottom = pos.y + m_Offset.y;

    CollisionSingleton::GetInstance().AddCollider(this, m_CollisionBox);
}

void diji::Collider::Update() // todo: not a fan, consider updating position when necessary rather than every frame, using dirty flag or other
{
    const auto& pos = m_TransformCompPtr->GetPosition();
    if ((std::is_eq( pos.x <=> m_CollisionBox.left) and std::is_eq(pos.y <=> m_CollisionBox.bottom)) or m_IsOffsetSet)
        return;

    m_CollisionBox.left = pos.x;
    m_CollisionBox.bottom = pos.y;

    CollisionSingleton::GetInstance().UpdateCollider(this, m_CollisionBox);
}