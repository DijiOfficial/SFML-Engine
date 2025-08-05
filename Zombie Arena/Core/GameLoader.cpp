#include "GameLoader.h"
#include "GameState.h"
#include "../Components/Player.h"
#include "../Input/CustomCommands.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"

using namespace diji;

// namespace global // todo: remove this and use the singleton with the window
// {
//     constexpr static sf::Vector2u VIEWPORT{ 1920, 1080 };
// }

void SceneLoader::ZombieArena() 
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif
    
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(zombieArena::GameState::Level));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(zombieArena::GameState::Level));

    const auto player = scene->CreateGameObject("X_Player");
    player->AddComponents<Transform>(25,25);
    player->AddComponents<TextureComp>("graphics/player.png");
    player->AddComponents<Render>();
    player->AddComponents<zombieArena::Player>();

#pragma region Commands
    auto& input = InputManager::GetInstance();
    
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Left, player, zombieArena::Movement::Left, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Left, player, zombieArena::Movement::Left, false);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Right, player, zombieArena::Movement::Right, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Right, player, zombieArena::Movement::Right, false);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Up, player, zombieArena::Movement::Top, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Up, player, zombieArena::Movement::Top, false);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Down, player, zombieArena::Movement::Bottom, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Down, player, zombieArena::Movement::Bottom, false);

    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::A, player, zombieArena::Movement::Left, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::A, player, zombieArena::Movement::Left, false);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::D, player, zombieArena::Movement::Right, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::D, player, zombieArena::Movement::Right, false);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::W, player, zombieArena::Movement::Top, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::W, player, zombieArena::Movement::Top, false);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::S, player, zombieArena::Movement::Bottom, true);
    input.BindCommand<zombieArena::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::S, player, zombieArena::Movement::Bottom, false);
#pragma endregion

#pragma region Observers
    // ball->GetComponent<pong::Ball>()->OnLifeLostEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::DecreaseScore);
    // ball->GetComponent<pong::Ball>()->OnIncreaseScoreEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    //
    // livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
    // livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
#pragma endregion
}
