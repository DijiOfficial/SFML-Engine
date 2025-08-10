#include "Crosshair.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Core/Engine.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Singleton/SceneManager.h"

void zombieArena::Crosshair::Init()
{
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();

    m_CameraCompPtr = diji::SceneManager::GetInstance().GetGameObject("X_Player")->GetComponent<diji::Camera>();

    window::g_window_ptr->setMouseCursorVisible(false);
}

void zombieArena::Crosshair::Update()
{
    const sf::Vector2i& mousePos = diji::InputManager::GetInstance().GetMousePosition();
    m_TransformCompPtr->SetPosition(static_cast<sf::Vector2f>(m_CameraCompPtr->GetMouseWorldPosition(mousePos)));
}