#include "Transform.h"
#include "../Core/GameObject.h"

void diji::Transform::Seek(const float speed)
{
    sf::Vector2f direction =  m_Target->GetPosition() - m_Position;

    if (direction == sf::Vector2f{ 0, 0 })
        return;

    direction = direction.normalized();
    const sf::Vector2f newPosition = m_Position + direction * speed * m_TimeSingleton.GetDeltaTime();

    SetPosition(newPosition);
}

void diji::Transform::SetTarget(const GameObject* target)
{
    m_Target = target->GetComponent<Transform>();
}
