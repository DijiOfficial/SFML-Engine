#include "GameLoader.h"
#include "GameState.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"

#include "Engine/Components/RectRender.h"
#include "Engine/Components/Transform.h"
#include "../Components/Paddle.h"
#include "../Inputs/CustomCommands.h"

using namespace diji;

namespace
{
    constexpr static sf::Vector2u VIEWPORT{ 1920, 1080 };
}

void SceneLoader::Pong()
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif
    
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(pong::GameState::Level));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(pong::GameState::Level));

    const auto paddle = scene->CreateGameObject("A_Paddle.png");
    paddle->AddComponents<Transform>(static_cast<float>(VIEWPORT.x) * 0.5f, static_cast<float>(VIEWPORT.y) - 20);
    paddle->AddComponents<RectRender>();
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f{50 , 5});
    shape.setPosition(sf::Vector2f{static_cast<float>(VIEWPORT.x) * 0.5f, static_cast<float>(VIEWPORT.y) - 20});
    paddle->GetComponent<RectRender>()->SetRectangle(shape);
    paddle->GetComponent<RectRender>()->SetFillColor(sf::Color::White);
    paddle->GetComponent<RectRender>()->SetLineWidth(0.f);
    paddle->AddComponents<pong::Paddle>();

#pragma region Commands
    auto& input = InputManager::GetInstance();

    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Left, paddle, pong::Movement::Left, true);
    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Left, paddle, pong::Movement::Left, false);
    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Right, paddle, pong::Movement::Right, true);
    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Right, paddle, pong::Movement::Right, false);
#pragma endregion
}
