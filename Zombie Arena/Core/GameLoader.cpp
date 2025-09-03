#include "GameLoader.h"

#include "GameState.h"
#include "../Components/BulletHudDisplay.h"
#include "../Components/Crosshair.h"
#include "../Components/CustomScoreCounter.h"
#include "../Components/GameManager.h"
#include "../Components/HealthBar.h"
#include "../Components/HighScore.h"
#include "../Components/Player.h"
#include "../Components/Pistol.h"
#include "../Components/Spawner.h"
#include "../Components/WaveCounter.h"
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
    SceneManager::GetInstance().RegisterScene(static_cast<int>(zombieArena::ZombieGameState::Level), ZombieArena);
    SceneManager::GetInstance().RegisterScene(static_cast<int>(zombieArena::ZombieGameState::StartMenu), StartMenu);
    SceneManager::GetInstance().RegisterScene(static_cast<int>(zombieArena::ZombieGameState::Upgrading), Upgrade);

    SceneManager::GetInstance().SetActiveScene(static_cast<int>(zombieArena::ZombieGameState::StartMenu));
    StartMenu();
}

void SceneLoader::ZombieArena() 
{
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(zombieArena::ZombieGameState::Level));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(zombieArena::ZombieGameState::Level));

    sf::IntRect arena{ sf::Vector2i{ 0, 0 }, zombieArena::GameManager::GetInstance().GetMapSize() };
    sf::IntRect arenaInner{ sf::Vector2i{ 50, 50 }, zombieArena::GameManager::GetInstance().GetMapSize() - sf::Vector2i{ 100, 100 } };
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
    pistol->AddComponents<zombieArena::Pistol>();
    
    // add arena to player constructor and make player collide with arena
    const auto player = scene->CreateGameObject("X_Player");
    player->AddComponents<Transform>(static_cast<float>(arena.size.x) * 0.5f, static_cast<float>(arena.size.y) * 0.5f);
    player->AddComponents<TextureComp>("graphics/player.png");
    player->AddComponents<Render>();
    player->AddComponents<zombieArena::Player>(arenaInner);
    player->GetComponent<zombieArena::Player>()->GivePistol(pistol);
    player->AddComponents<Collider>();
    player->AddComponents<Camera>(1920.f, 1080.f);
    player->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));
    pistol->SetParent(player, false);

    zombieArena::GameManager::GetInstance().Init(); // pass the area
    
    const auto background = scene->CreateGameObject("A_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<Sprite>("graphics/background_sheet.png", 50, 5, arena.size.x, arena.size.y);
    background->GetComponent<Sprite>()->SetTileCount(1, 4);
    background->GetComponent<Sprite>()->SetWallSpritePosition(sf::FloatRect{ sf::Vector2f{ 0, 150 }, sf::Vector2f{ 50, 50 } });
    background->AddComponents<Render>();

    const auto spawner = scene->CreateGameObject("Spawner");
    spawner->AddComponents<Transform>(0, 0);
    spawner->AddComponents<zombieArena::Spawner>(player, arena);

    const auto crosshair = scene->CreateGameObject("Z_Crosshair");
    crosshair->AddComponents<Transform>(0, 0);
    crosshair->AddComponents<TextureComp>("graphics/crosshair.png");
    crosshair->GetComponent<TextureComp>()->SetOriginToCenter();
    crosshair->AddComponents<Render>();
    crosshair->AddComponents<zombieArena::Crosshair>();

#pragma region HUD
    const auto fpsCounter = scene->CreateGameObject("Z_FPSCounter");
    fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/digital-7.ttf", sf::Color::White, true);
    fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    fpsCounter->AddComponents<FPSCounter>();
    fpsCounter->AddComponents<Transform>(static_cast<int>(1920 - 100.f), 40);
    fpsCounter->AddComponents<Render>();
    
    const auto highScore = scene->CreateGameObject("Z_highScoreHUD");
    highScore->AddComponents<Transform>(1400, 0);
    highScore->AddComponents<TextComp>("HIGH SCORE: 0", "fonts/zombiecontrol.ttf");
    highScore->GetComponent<TextComp>()->GetText().setCharacterSize(55);
    highScore->AddComponents<Render>();
    highScore->AddComponents<zombieArena::HighScore>();
    highScore->GetComponent<zombieArena::HighScore>()->SetString("HIGH SCORE: ");
    scene->SetGameObjectAsCanvasObject(highScore);

    const auto ammoText = scene->CreateGameObject("Z_ammoTextHUD");
    ammoText->AddComponents<Transform>(200, 980);
    ammoText->AddComponents<TextComp>("24/24", "fonts/zombiecontrol.ttf");
    ammoText->GetComponent<TextComp>()->GetText().setCharacterSize(55);
    ammoText->AddComponents<Render>();
    ammoText->AddComponents<zombieArena::BulletHudDisplay>();

    const auto scoreText = scene->CreateGameObject("Z_scoreTextHUD");
    scoreText->AddComponents<Transform>(20, 0);
    scoreText->AddComponents<TextComp>("SCORE: 0", "fonts/zombiecontrol.ttf");
    scoreText->GetComponent<TextComp>()->GetText().setCharacterSize(55);
    scoreText->AddComponents<Render>();
    scoreText->AddComponents<zombieArena::CustomScoreCounter>(zombieArena::GameManager::GetInstance().GetCurrentPlayerScore());
    scoreText->GetComponent<zombieArena::CustomScoreCounter>()->SetString("Score:");
    scoreText->GetComponent<zombieArena::CustomScoreCounter>()->SetScoreIncreaseIncrement(10);

    const auto zombiesRemainingText = scene->CreateGameObject("Z_zombiesRemainingTextHUD");
    zombiesRemainingText->AddComponents<Transform>(1500, 980);
    zombiesRemainingText->AddComponents<TextComp>("Zombies: 100", "fonts/zombiecontrol.ttf");
    zombiesRemainingText->GetComponent<TextComp>()->GetText().setCharacterSize(55);
    zombiesRemainingText->AddComponents<Render>();
    zombiesRemainingText->AddComponents<ScoreCounter>(0);
    zombiesRemainingText->GetComponent<ScoreCounter>()->SetString("Zombies: ");
    zombiesRemainingText->GetComponent<ScoreCounter>()->SetGoalScore(0);

    const auto waveNumberText = scene->CreateGameObject("Z_waveNumberTextHUD");
    waveNumberText->AddComponents<Transform>(1250, 980);
    waveNumberText->AddComponents<TextComp>("Wave: 0", "fonts/zombiecontrol.ttf");
    waveNumberText->GetComponent<TextComp>()->GetText().setCharacterSize(55);
    waveNumberText->AddComponents<Render>();
    waveNumberText->AddComponents<zombieArena::WaveCounter>();
    waveNumberText->GetComponent<zombieArena::WaveCounter>()->SetString("Wave: ");
    
    const auto healthBar = scene->CreateGameObject("Z_healthBarHUD");
    healthBar->AddComponents<Transform>(650, 980);
    healthBar->AddComponents<RectRender>();
    
    sf::RectangleShape rect2;
    rect2.setSize(sf::Vector2f{545 , 125});

    healthBar->GetComponent<RectRender>()->SetRectangle(rect2);
    healthBar->GetComponent<RectRender>()->SetFillColor(sf::Color::Red);
    healthBar->GetComponent<RectRender>()->SetLineWidth(0.f);
    healthBar->AddComponents<zombieArena::HealthBar>();
    
    scene->SetGameObjectAsCanvasObject("Z_ammoTextHUD");
    scene->SetGameObjectAsCanvasObject("Z_scoreTextHUD");
    scene->SetGameObjectAsCanvasObject("Z_zombiesRemainingTextHUD");
    scene->SetGameObjectAsCanvasObject("Z_waveNumberTextHUD");
    scene->SetGameObjectAsCanvasObject("Z_healthBarHUD");
    scene->SetGameObjectAsCanvasObject("Z_FPSCounter");
#pragma endregion
    
#pragma region Commands
    auto& input = InputManager::GetInstance();
    // todo: Find a way to keep commands updated on scene change or automatically delete them when scene is create deleted!
    input.ResetCommands();
    
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
    pistol->GetComponent<zombieArena::Pistol>()->OnAmmoChangedEvent.AddListener(ammoText->GetComponent<zombieArena::BulletHudDisplay>(), &zombieArena::BulletHudDisplay::UpdateText);
    zombieArena::GameManager::GetInstance().OnPickedUpEvent.AddListener(player->GetComponent<zombieArena::Player>(), &zombieArena::Player::HandlePickups);
    zombieArena::GameManager::GetInstance().OnZombieKilledEvent.AddListener(scoreText->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    zombieArena::GameManager::GetInstance().OnZombieKilledEvent.AddListener(zombiesRemainingText->GetComponent<ScoreCounter>(), &ScoreCounter::DecreaseScore);
    scoreText->GetComponent<ScoreCounter>()->OnScoreIncreasedEvent.AddListener(highScore->GetComponent<zombieArena::HighScore>(), &zombieArena::HighScore::UpdateScore);
    scoreText->GetComponent<zombieArena::CustomScoreCounter>()->OnScoreSetEvent.AddListener(highScore->GetComponent<zombieArena::HighScore>(), &zombieArena::HighScore::UpdateScore);
    spawner->GetComponent<zombieArena::Spawner>()->OnWaveSpawnedEvent.AddListener(zombiesRemainingText->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    zombiesRemainingText->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(&zombieArena::GameManager::GetInstance(), &zombieArena::GameManager::IncrementCurrentWave);
    zombiesRemainingText->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(pistol->GetComponent<zombieArena::Pistol>(), &zombieArena::Pistol::SaveInfo);
    zombiesRemainingText->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(scoreText->GetComponent<zombieArena::CustomScoreCounter>(), &zombieArena::CustomScoreCounter::SaveScore);
    player->GetComponent<zombieArena::Player>()->OnHealthChangeEvent.AddListener(healthBar->GetComponent<zombieArena::HealthBar>(), &zombieArena::HealthBar::UpdateHealthBar);
    player->GetComponent<zombieArena::Player>()->OnDeathEvent.AddListener(&zombieArena::GameManager::GetInstance(), &zombieArena::GameManager::Reset);
    player->GetComponent<zombieArena::Player>()->OnDeathEvent.AddListener(highScore->GetComponent<zombieArena::HighScore>(), &zombieArena::HighScore::SaveHighScore);

    // ball->GetComponent<pong::Ball>()->OnIncreaseScoreEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    
    // livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
    // livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
#pragma endregion
}

void SceneLoader::StartMenu()
{
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(zombieArena::ZombieGameState::StartMenu));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(zombieArena::ZombieGameState::StartMenu));
    constexpr sf::IntRect arena{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 1920, 1080 } };

    const auto background = scene->CreateGameObject("A_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<TextureComp>("graphics/background.png");
    background->AddComponents<Render>();
    background->AddComponents<Camera>(1920.f, 1080.f);
    background->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));

    // set up a camera and use the camera instead of the window sizes
    const auto HUD = scene->CreateGameObject("Z_HUD");
    HUD->AddComponents<Transform>(0, 0);

    const auto startText = scene->CreateGameObject("Z_playerTextHUD");
    startText->AddComponents<Transform>(250, 850);
    startText->AddComponents<TextComp>("PRESS ENTER TO PLAY", "fonts/zombiecontrol.ttf");
    startText->GetComponent<TextComp>()->GetText().setCharacterSize(125);
    startText->AddComponents<Render>();
    startText->SetParent(HUD, true);

    const auto highScore = scene->CreateGameObject("Z_highScoreHUD");
    highScore->AddComponents<Transform>(1400, 0);
    highScore->AddComponents<TextComp>("HIGH SCORE: 0", "fonts/zombiecontrol.ttf");
    highScore->GetComponent<TextComp>()->GetText().setCharacterSize(55);
    highScore->AddComponents<Render>();
    highScore->SetParent(HUD, true);
    highScore->AddComponents<zombieArena::HighScore>();
    highScore->GetComponent<zombieArena::HighScore>()->SetString("HIGH SCORE: ");
    
    const auto fpsCounter = scene->CreateGameObject("Z_FPSCounter");
    fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/digital-7.ttf", sf::Color::White, true);
    fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    fpsCounter->AddComponents<FPSCounter>();
    fpsCounter->AddComponents<Transform>(static_cast<int>(1920 - 100.f), 40);
    fpsCounter->AddComponents<Render>();
    
#pragma region Commands
    auto& input = InputManager::GetInstance();
    
    input.BindCommand<zombieArena::Start>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Enter, startText, zombieArena::ZombieGameState::Upgrading);
#pragma endregion
}

void SceneLoader::Upgrade()
{
    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(zombieArena::ZombieGameState::Upgrading));
    GameStateManager::GetInstance().SetNewGameState(static_cast<GameState>(zombieArena::ZombieGameState::Upgrading));
    constexpr sf::IntRect arena{ sf::Vector2i{ 0, 0 }, sf::Vector2i{ 1920, 1080 } };

    const auto background = scene->CreateGameObject("A_Background");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<TextureComp>("graphics/background.png");  
    background->AddComponents<Render>();
    background->AddComponents<Camera>(1920.f, 1080.f);
    background->GetComponent<Camera>()->SetLevelBoundaries(static_cast<sf::FloatRect>(arena));

    // set up a camera and use the camera instead of the window sizes
    const auto HUD = scene->CreateGameObject("Z_HUD");
    HUD->AddComponents<Transform>(0, 0);
    
    const auto startText = scene->CreateGameObject("Z_playerTextHUD");
    startText->AddComponents<Transform>(150, 250);
    startText->AddComponents<TextComp>("1- Increased rate of fire\n2- Increased clip size(next reload)\n3- Increased max health\n4- Increased run speed\n5- More and better health pickups\n6- More and better ammo pickups", "fonts/zombiecontrol.ttf");
    startText->GetComponent<TextComp>()->GetText().setCharacterSize(80);
    startText->AddComponents<Render>();
    startText->SetParent(HUD, true);
    
    const auto fpsCounter = scene->CreateGameObject("Z_FPSCounter");
    fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/digital-7.ttf", sf::Color::White, true);
    fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    fpsCounter->AddComponents<FPSCounter>();
    fpsCounter->AddComponents<Transform>(static_cast<int>(1920 - 100.f), 40);
    fpsCounter->AddComponents<Render>();
    
#pragma region Commands
    auto& input = InputManager::GetInstance();
    
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Num1, startText, zombieArena::UpgradeType::FIRE_RATE);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Numpad1, startText, zombieArena::UpgradeType::FIRE_RATE);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Num2, startText, zombieArena::UpgradeType::CLIP_SIZE);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Numpad2, startText, zombieArena::UpgradeType::CLIP_SIZE);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Num3, startText, zombieArena::UpgradeType::HEALTH);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Numpad3, startText, zombieArena::UpgradeType::HEALTH);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Num4, startText, zombieArena::UpgradeType::SPEED);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Numpad4, startText, zombieArena::UpgradeType::SPEED);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Num5, startText, zombieArena::UpgradeType::HEALTH_PICKUP);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Numpad5, startText, zombieArena::UpgradeType::HEALTH_PICKUP);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Num6, startText, zombieArena::UpgradeType::AMMO_PICKUP);
    input.BindCommand<zombieArena::UpgradeChoice>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Numpad6, startText, zombieArena::UpgradeType::AMMO_PICKUP);
#pragma endregion
}
