#include "GameLoader.h"

#include "GameState.h"
#include "../Input/CustomCommands.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine//Collision/Collider.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/FPSCounter.h"
#include "Engine/Components/RectRender.h"
#include "Engine/Components/ScoreCounter.h"
#include "Engine/Components/Sprite.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Core/Engine.h"
#include "Engine/Singleton/GameStateManager.h"

using namespace diji;

void SceneLoader::GameStartUp()
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif

    //todo: this would be better if it was part of the CreateScene function.
    SceneManager::GetInstance().RegisterScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level), Level);
    Level();
}

void SceneLoader::StartMenu(){}

void SceneLoader::Level()
{
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level));
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(thomasWasLate::thomasWasLateState::Level));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(thomasWasLate::thomasWasLateState::Level));
    constexpr sf::IntRect arena{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 1920, 1080 } };

    const auto background = scene->CreateGameObject("A_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<TextureComp>("graphics/background.png");
    background->AddComponents<Render>();
    background->AddComponents<Camera>(window::VIEWPORT);
    background->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));

    // // set up a camera and use the camera instead of the window sizes
    // const auto HUD = scene->CreateGameObject("Z_HUD");
    // HUD->AddComponents<Transform>(0, 0);
    //
    // const auto startText = scene->CreateGameObject("Z_playerTextHUD");
    // startText->AddComponents<Transform>(250, 850);
    // startText->AddComponents<TextComp>("PRESS ENTER TO PLAY", "fonts/zombiecontrol.ttf");
    // startText->GetComponent<TextComp>()->GetText().setCharacterSize(125);
    // startText->AddComponents<Render>();
    // startText->SetParent(HUD, true);
    //
    // const auto fpsCounter = scene->CreateGameObject("Z_FPSCounter");
    // fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/digital-7.ttf", sf::Color::White, true);
    // fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    // fpsCounter->AddComponents<FPSCounter>();
    // fpsCounter->AddComponents<Transform>(static_cast<int>(1920 - 100.f), 40);
    // fpsCounter->AddComponents<Render>();
    
#pragma region Commands
    auto& input = InputManager::GetInstance();

    input.BindCommand<thomasWasLate::SwitchSplitScreenView>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::E, nullptr);
#pragma endregion
}