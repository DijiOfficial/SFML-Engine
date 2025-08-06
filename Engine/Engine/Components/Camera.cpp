#include "Camera.h"
#include "../Core/Engine.h"
#include "../Core/GameObject.h"
#include "Transform.h"

diji::Camera::Camera(GameObject* ownerPtr, const float width, const float height)
    : Component(ownerPtr)
    , m_LevelBoundaries{ sf::Vector2f{ 0, 0 }, sf::Vector2f{ width, height } } 
    , m_Width{ width }
    , m_Height{ height }
    , m_CameraOffset{ 0 }
    , m_IsLocked{ false }
{
    m_CameraView = sf::View(sf::Vector2f{ 0, 0 }, sf::Vector2f{ width, height });
}

void diji::Camera::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<Transform>();
    window::g_window_ptr->setView(m_CameraView);
}

void diji::Camera::SetFollow(const GameObject* target)
{
    (void)target;
}

void diji::Camera::SetFollowSelf()
{
}

void diji::Camera::SetAsMainView() const
{
    window::g_window_ptr->setView(m_CameraView);
}

sf::Vector2i diji::Camera::GetMouseWorldPosition(const sf::Vector2i& pos) const
{
    return static_cast<sf::Vector2i>(window::g_window_ptr->mapPixelToCoords(pos, m_CameraView));
}
