#include "GameLoader.h"
#include "GameState.h"
#include "../Components/Ball.h"
#include "Engine/Singleton/SceneManager.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"

#include "Engine/Components/RectRender.h"
#include "Engine/Components/Transform.h"
#include "../Components/Paddle.h"
#include "../Inputs/CustomCommands.h"
#include "Engine/Collision/Collider.h"
#include "Engine/Components/ScoreCounter.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Core/Engine.h"

using namespace diji;

void SceneLoader::Pong()
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif

    const auto& scene = SceneManager::GetInstance().CreateScene(static_cast<int>(pong::GameState::Level));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(pong::GameState::Level));

    const auto paddle = scene->CreateGameObject("A_Paddle");
    paddle->AddComponents<Transform>(static_cast<float>(window::VIEWPORT.x) * 0.5f, static_cast<float>(window::VIEWPORT.y) - 20);
    paddle->AddComponents<RectRender>();
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f{50 , 5});
    shape.setPosition(sf::Vector2f{static_cast<float>(window::VIEWPORT.x) * 0.5f, static_cast<float>(window::VIEWPORT.y) - 20});
    paddle->GetComponent<RectRender>()->SetRectangle(shape);
    paddle->GetComponent<RectRender>()->SetFillColor(sf::Color::White);
    paddle->GetComponent<RectRender>()->SetLineWidth(0.f);
    paddle->AddComponents<pong::Paddle>();
    paddle->AddComponents<Collider>(50, 5);

    const auto ball = scene->CreateGameObject("A_Ball");
    ball->AddComponents<Transform>(static_cast<float>(window::VIEWPORT.x) * 0.5f, 0.0f);

    // look into optimizing this redundant code
    ball->AddComponents<RectRender>();
    sf::RectangleShape ballShape;
    ballShape.setSize(sf::Vector2f{10 , 10});
    ballShape.setPosition(sf::Vector2f{static_cast<float>(window::VIEWPORT.x) * 0.5f, static_cast<float>(window::VIEWPORT.y) - 20});
    ball->GetComponent<RectRender>()->SetRectangle(ballShape);
    ball->GetComponent<RectRender>()->SetFillColor(sf::Color::White);
    ball->GetComponent<RectRender>()->SetLineWidth(0.f);

    ball->AddComponents<pong::Ball>();
    ball->AddComponents<Collider>(10, 10);

    const auto scoreCounter = scene->CreateGameObject("Z_scoreCounterHUD");
    scoreCounter->AddComponents<TextComp>("Score: 0", "fonts/digital-7.ttf", sf::Color::White);
    scoreCounter->GetComponent<TextComp>()->GetText().setCharacterSize(75);
    scoreCounter->AddComponents<ScoreCounter>(0);
    scoreCounter->GetComponent<ScoreCounter>()->SetString("Score:");
    scoreCounter->AddComponents<Transform>(20, 20);
    scoreCounter->AddComponents<Render>();

    const auto livesCounter = scene->CreateGameObject("Z_livesCounterHUD");
    livesCounter->AddComponents<TextComp>("Lives: 3", "fonts/digital-7.ttf", sf::Color::White);
    livesCounter->GetComponent<TextComp>()->GetText().setCharacterSize(75);
    livesCounter->AddComponents<ScoreCounter>(3);
    livesCounter->GetComponent<ScoreCounter>()->SetString("Lives:");
    livesCounter->GetComponent<ScoreCounter>()->SetGoalScore(0);
    livesCounter->AddComponents<Transform>(350, 20);
    livesCounter->AddComponents<Render>();

#pragma region Commands
    auto& input = InputManager::GetInstance();

    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Left, paddle, pong::Movement::Left, true);
    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Left, paddle, pong::Movement::Left, false);
    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Right, paddle, pong::Movement::Right, true);
    input.BindCommand<pong::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::RELEASED, sf::Keyboard::Scancode::Right, paddle, pong::Movement::Right, false);
#pragma endregion

#pragma region Observers
       ball->GetComponent<pong::Ball>()->OnLifeLostEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::DecreaseScore);
    ball->GetComponent<pong::Ball>()->OnIncreaseScoreEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    
    livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(livesCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
    livesCounter->GetComponent<ScoreCounter>()->OnGivenScoreReachedEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
#pragma endregion
}
