#include "GameLoader.h"

#include "GameState.h"
#include "../Components/Player.h"
#include "../Components/Pistol.h"
#include "../Components/Spawner.h"
#include "../Input/CustomCommands.h"
#include "Engine/Collision/CollisionSingleton.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/Camera.h"
#include "Engine/Components/FPSCounter.h"
#include "Engine/Components/Sprite.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Singleton/GameStateManager.h"

using namespace diji;

void SceneLoader::ZombieArena() 
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif
    
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(zombieArena::ZombieGameState::GameOver));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(zombieArena::ZombieGameState::GameOver));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(zombieArena::ZombieGameState::GameOver));

    sf::IntRect arena{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 2000, 1100 } };
    constexpr int TILE_SIZE = 50;
    const Rectf rectfArena
    {
        .left = static_cast<float>(arena.position.x + TILE_SIZE),
        .bottom = static_cast<float>(arena.position.y + TILE_SIZE),
        .width = static_cast<float>(arena.size.x - TILE_SIZE),
        .height = static_cast<float>(arena.size.y - TILE_SIZE)
    };
    CollisionSingleton::GetInstance().ParseRectInLevelCollider(rectfArena);

    const auto pistol = scene->CreateGameObject("Pistol");
    pistol->AddComponents<Transform>(0, 0);
    pistol->AddComponents<zombieArena::Pistol>(1.0f, 6, 24);
    
    // add arena to player constructor and make player collide with arena
    const auto player = scene->CreateGameObject("X_Player");
    player->AddComponents<Transform>(arena.size.x * 0.5f, arena.size.y * 0.5f);
    player->AddComponents<TextureComp>("graphics/player.png");
    player->AddComponents<Render>();
    player->AddComponents<zombieArena::Player>(arena);
    player->GetComponent<zombieArena::Player>()->GivePistol(pistol);
    player->AddComponents<Camera>(1920.f, 1080.f);
    player->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));
    pistol->SetParent(player, false);
    
    const auto tempBackground = scene->CreateGameObject("Background");
    tempBackground->AddComponents<Transform>(0, 0);
    tempBackground->AddComponents<Sprite>("graphics/background_sheet.png", 50, 5, arena.size.x, arena.size.y);
    tempBackground->GetComponent<Sprite>()->SetTileCount(1, 4);
    tempBackground->GetComponent<Sprite>()->SetWallSpritePosition(sf::FloatRect{ sf::Vector2f{ 0, 150 }, sf::Vector2f{ 50, 50 } });
    tempBackground->AddComponents<Render>();

    const auto fpsCounter = scene->CreateGameObject("fpsCounter");
    fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/digital-7.ttf", sf::Color::White, true);
    fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    fpsCounter->AddComponents<FPSCounter>();
    fpsCounter->AddComponents<Transform>(static_cast<int>(1920 - 100.f), 40);
    fpsCounter->AddComponents<Render>();

    // const auto spawnerTest = scene->CreateGameObject("SpawnerTest");
    // spawnerTest->AddComponents<Transform>(0, 0);
    // spawnerTest->AddComponents<zombieArena::Spawner>(player, arena);
    
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

    input.BindMouseMoveCommand<zombieArena::Aim>(player);
    input.BindCommand<zombieArena::Pause>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Enter, player);

    input.BindCommand<zombieArena::Shoot>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Mouse::Button::Left, player, true);
    input.BindCommand<zombieArena::Shoot>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Mouse::Button::Left, player, false); // release is not needed for semi auto weapons
    input.BindCommand<zombieArena::Reload>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::R, player);
#pragma endregion

#pragma region Observers
    // ball->GetComponent<pong::Ball>()->OnLifeLostEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::DecreaseScore);
    // ball->GetComponent<pong::Ball>()->OnIncreaseScoreEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    //
    // livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
    // livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
#pragma endregion
}
