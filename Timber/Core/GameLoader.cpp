#include "GameLoader.h"

#include <SFML/Graphics/Color.hpp>

#include "GameStates.h"
#include "../Components/AxeBehaviour.h"
#include "../Components/Beehaviour.h"
#include "../Components/BranchBehaviour.h"
#include "../Components/CloudBehaviour.h"
#include "../Components/GravestoneBehaviour.h"
#include "../Components/LogBehaviour.h"
#include "../Components/PauseBehaviourText.h"
#include "../Components/PlayerBehaviour.h"
#include "../Components/TimeBar.h"
#include "../Inputs/CustomCommands.h"
#include "../Singleton/GameManager.h"
#include "Engine/Components/FPSCounter.h"
#include "Engine/Components/RectRender.h"

#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Components/ScoreCounter.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Interfaces/ISoundSystem.h"

using namespace diji;

// todo: game is made for 1920x1080 resolution based on the book, Not ideal and not scalable. Magic numbers based on window size can be replaced by getting viewport from window::g_window_ptr
void SceneLoader::Timber()
{
#ifndef NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SFMLISoundSystem>()));
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<SFMLISoundSystem>());
#endif
    
    const auto& timberScene = SceneManager::GetInstance().CreateScene(static_cast<int>(timber::GameState::Level));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(timber::GameState::Level));

    timber::GameManager::GetInstance().SetNewGameState(timber::GameState::Level);

    const auto background = timberScene->CreateGameObject("A_BackgroundLevel.png");
    background->AddComponents<TextureComp>("graphics/background.png");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<Render>();

    const auto tree = timberScene->CreateGameObject("E_tree");
    tree->AddComponents<TextureComp>("graphics/tree.png");
    tree->AddComponents<Transform>(810, 0);
    tree->AddComponents<Render>();

    const auto tree2 = timberScene->CreateGameObject("D_tree2");
    tree2->AddComponents<TextureComp>("graphics/tree2.png");
    tree2->AddComponents<Transform>(20, 0);
    tree2->AddComponents<Render>();
    tree2->GetComponent<TextureComp>()->SetScaleX(0.5f);
    tree2->GetComponent<TextureComp>()->SetScaleY(1.2f);

    const auto tree3 = timberScene->CreateGameObject("BA_tree3", tree2);
    tree3->GetComponent<Transform>()->SetPosition(355, 0);
    tree3->GetComponent<TextureComp>()->SetScaleX(0.58f);
    tree3->GetComponent<TextureComp>()->SetScaleY(0.85f);

    const auto tree4 = timberScene->CreateGameObject("D_tree4", tree2);
    tree4->GetComponent<Transform>()->SetPosition(1333, 0);
    tree4->GetComponent<TextureComp>()->SetScaleX(0.61f);
    tree4->GetComponent<TextureComp>()->SetScaleY(0.87f);

    const auto tree5 = timberScene->CreateGameObject("BA_tree5", tree2);
    tree5->GetComponent<Transform>()->SetPosition(1586, 0);
    tree5->GetComponent<TextureComp>()->SetScaleX(0.68f);
    tree5->GetComponent<TextureComp>()->SetScaleY(0.76f);
    
    const auto bee = timberScene->CreateGameObject("B_bee");
    bee->AddComponents<TextureComp>("graphics/bee.png");
    bee->AddComponents<Transform>(0, 800);
    bee->AddComponents<Render>();
    bee->AddComponents<timber::Beehaviour>();

    (void)timberScene->CreateGameObject("B_bee2", bee);
    (void)timberScene->CreateGameObject("B_bee3", bee);
    (void)timberScene->CreateGameObject("B_bee4", bee);

    const auto cloud = timberScene->CreateGameObject("C_cloud");
    cloud->AddComponents<TextureComp>("graphics/cloud.png");
    cloud->AddComponents<Transform>(0, 0);
    cloud->AddComponents<Render>();
    cloud->AddComponents<timber::CloudBehaviour>(0.f, 150.f, 0.65f);
    
    const auto cloud2 = timberScene->CreateGameObject("C_cloud2", cloud);
    cloud2->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 150);

    const auto cloud3 = timberScene->CreateGameObject("C_cloud3", cloud);
    cloud3->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 350);

    const auto cloud4 = timberScene->CreateGameObject("C_cloud4", cloud);
    cloud4->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 350);

    const auto cloud5 = timberScene->CreateGameObject("C_cloud5", cloud);
    cloud5->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 350);
    
    const auto HUD = timberScene->CreateGameObject("Z_HUD");
    HUD->AddComponents<Transform>(0, 0);

    const auto scoreCounter = timberScene->CreateGameObject("Z_scoreCounterHUD");
    // todo: if we want to decouple more we can inherit from TextComp and create a new comp that listens on ScoreCounter to update itself.
    scoreCounter->AddComponents<TextComp>("Score = 0", "fonts/KOMIKAP_.ttf", sf::Color::White);
    scoreCounter->GetComponent<TextComp>()->GetText().setCharacterSize(100);
    scoreCounter->AddComponents<ScoreCounter>(0);
    scoreCounter->AddComponents<Transform>(20, 20);
    scoreCounter->AddComponents<Render>();
    scoreCounter->SetParent(HUD, false);

    const auto pauseText = timberScene->CreateGameObject("Z_pauseTextHUD");
    pauseText->AddComponents<TextComp>("Press Enter to start!", "fonts/KOMIKAP_.ttf", sf::Color::White, true);
    pauseText->GetComponent<TextComp>()->GetText().setCharacterSize(75);
    pauseText->AddComponents<Transform>(960, 540); // use viewport width/height
    pauseText->AddComponents<timber::PauseBehaviourText>();
    pauseText->AddComponents<Render>();
    pauseText->GetComponent<Render>()->DisableRender();
    pauseText->SetParent(HUD, false);

    const auto timeBar = timberScene->CreateGameObject("Z_timeBarHUD");
    timeBar->AddComponents<Transform>(760, 940);
    timeBar->AddComponents<RectRender>();
    
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f{400 , 80});
    rect.setPosition(sf::Vector2f{760, 980});

    timeBar->GetComponent<RectRender>()->SetRectangle(rect);
    timeBar->GetComponent<RectRender>()->SetFillColor(sf::Color::Red);
    timeBar->GetComponent<RectRender>()->SetLineWidth(0.f);
    timeBar->AddComponents<timber::TimeBar>();
    timeBar->SetParent(HUD, false);
    
    const auto firstBranch = timberScene->CreateGameObject("E_firstBranch");
    firstBranch->AddComponents<TextureComp>("graphics/branch.png");
    firstBranch->GetComponent<TextureComp>()->SetOrigin(220, 20);
    firstBranch->AddComponents<Transform>(-2000, -2000);
    firstBranch->AddComponents<Render>();
    firstBranch->AddComponents<timber::BranchBehaviour>();
    firstBranch->GetComponent<timber::BranchBehaviour>()->SetHeight(0);

    const auto secondBranch = timberScene->CreateGameObject("E_secondBranch", firstBranch);
    secondBranch->GetComponent<timber::BranchBehaviour>()->SetHeight(150);
    secondBranch->GetComponent<TextureComp>()->SetOrigin(220, 20);

    const auto thirdBranch = timberScene->CreateGameObject("E_thirdBranch", firstBranch);
    thirdBranch->GetComponent<timber::BranchBehaviour>()->SetHeight(300);
    thirdBranch->GetComponent<TextureComp>()->SetOrigin(220, 20);

    const auto fourthBranch = timberScene->CreateGameObject("E_fourthBranch", firstBranch);
    fourthBranch->GetComponent<timber::BranchBehaviour>()->SetHeight(450);
    fourthBranch->GetComponent<TextureComp>()->SetOrigin(220, 20);

    const auto fifthBranch = timberScene->CreateGameObject("E_fifthBranch", firstBranch);
    fifthBranch->GetComponent<timber::BranchBehaviour>()->SetHeight(600);
    fifthBranch->GetComponent<TextureComp>()->SetOrigin(220, 20);

    const auto sixthBranch = timberScene->CreateGameObject("E_sixthBranch", firstBranch);
    sixthBranch->GetComponent<timber::BranchBehaviour>()->SetHeight(750);
    sixthBranch->GetComponent<TextureComp>()->SetOrigin(220, 20);

    
    const auto player = timberScene->CreateGameObject("X_player");
    player->AddComponents<Transform>(580, 720);
    player->AddComponents<TextureComp>("graphics/player.png");
    player->AddComponents<Render>();
    player->AddComponents<timber::PlayerBehaviour>();

    const auto gravestone = timberScene->CreateGameObject("X_gravestone");
    gravestone->AddComponents<Transform>(600, 860);
    gravestone->AddComponents<TextureComp>("graphics/rip.png");
    gravestone->AddComponents<Render>();
    gravestone->GetComponent<Render>()->DisableRender();
    gravestone->AddComponents<timber::GravestoneBehaviour>();

    const auto axe = timberScene->CreateGameObject("Z_axe");
    axe->AddComponents<Transform>(700, 830);
    axe->AddComponents<TextureComp>("graphics/axe.png");
    axe->AddComponents<Render>();
    axe->AddComponents<timber::AxeBehaviour>();
    axe->SetParent(player, true);

    const auto flyingLog = timberScene->CreateGameObject("W_flyingLog");
    flyingLog->AddComponents<Transform>(960, 840);
    flyingLog->AddComponents<TextureComp>("graphics/log.png");
    flyingLog->AddComponents<Render>();
    flyingLog->AddComponents<timber::LogBehaviour>();
    
    const auto backgroundUI = timberScene->CreateGameObject("Z_backgroundUIHUD");
    backgroundUI->AddComponents<Transform>(20, 20);
    backgroundUI->AddComponents<RectRender>();
    
    sf::RectangleShape rect2;
    rect2.setSize(sf::Vector2f{545 , 125});
    rect2.setPosition(sf::Vector2f{15, 15});

    backgroundUI->GetComponent<RectRender>()->SetRectangle(rect2);
    backgroundUI->GetComponent<RectRender>()->SetFillColor(sf::Color(0, 0, 0, 150));
    backgroundUI->GetComponent<RectRender>()->SetLineWidth(0.f);
    
    const auto fpsCounter = timberScene->CreateGameObject("fpsCounter");
    fpsCounter->AddComponents<TextComp>("0 FPS", "fonts/KOMIKAP_.ttf", sf::Color::White, true);
    fpsCounter->GetComponent<TextComp>()->GetText().setCharacterSize(33);
    fpsCounter->AddComponents<FPSCounter>();
    fpsCounter->AddComponents<Transform>(static_cast<int>(1920 - 100.f), 40);
    fpsCounter->AddComponents<Render>();

    const auto backgroundUI2 = timberScene->CreateGameObject("Z_backgroundUI2HUD");
    backgroundUI2->AddComponents<Transform>(20, 20);
    backgroundUI2->AddComponents<RectRender>();
    
    sf::RectangleShape rect3;
    rect3.setSize(sf::Vector2f{180 , 50});
    rect3.setPosition(sf::Vector2f{static_cast<int>(1920 - 190.f), 15});

    backgroundUI2->GetComponent<RectRender>()->SetRectangle(rect3);
    backgroundUI2->GetComponent<RectRender>()->SetFillColor(sf::Color(0, 0, 0, 150));
    backgroundUI2->GetComponent<RectRender>()->SetLineWidth(0.f);
#pragma region Observers
    player->GetComponent<timber::PlayerBehaviour>()->OnPauseEvent.AddListener(pauseText->GetComponent<timber::PauseBehaviourText>(), &timber::PauseBehaviourText::RefreshDisplay);
    timeBar->GetComponent<timber::TimeBar>()->OnGameOverEvent.AddListener(pauseText->GetComponent<timber::PauseBehaviourText>(), &timber::PauseBehaviourText::OnGameOver);

    player->GetComponent<timber::PlayerBehaviour>()->OnRestartEvent.AddListener(timeBar->GetComponent<timber::TimeBar>(), &timber::TimeBar::Reset);
    player->GetComponent<timber::PlayerBehaviour>()->OnRestartEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::Reset);
    player->GetComponent<timber::PlayerBehaviour>()->OnRestartEvent.AddListener(pauseText->GetComponent<timber::PauseBehaviourText>(), &timber::PauseBehaviourText::Reset);
    player->GetComponent<timber::PlayerBehaviour>()->OnRestartEvent.AddListener(axe->GetComponent<timber::AxeBehaviour>(), &timber::AxeBehaviour::Reset);
    player->GetComponent<timber::PlayerBehaviour>()->OnRestartEvent.AddListener(gravestone->GetComponent<timber::GravestoneBehaviour>(), &timber::GravestoneBehaviour::Reset);

    player->GetComponent<timber::PlayerBehaviour>()->OnPlayerMovedEvent.AddListener(scoreCounter->GetComponent<ScoreCounter>(), &ScoreCounter::IncreaseScore);
    scoreCounter->GetComponent<ScoreCounter>()->OnScoreIncreasedEvent.AddListener(timeBar->GetComponent<timber::TimeBar>(), &timber::TimeBar::AddTime);
    player->GetComponent<timber::PlayerBehaviour>()->OnPlayerMovedEvent.AddListener(axe->GetComponent<timber::AxeBehaviour>(), &timber::AxeBehaviour::SetPosition);
    player->GetComponent<timber::PlayerBehaviour>()->OnPlayerMovedEvent.AddListener(flyingLog->GetComponent<timber::LogBehaviour>(), &timber::LogBehaviour::Activate);
    player->GetComponent<timber::PlayerBehaviour>()->OnPlayerMovedEvent.AddListener(gravestone->GetComponent<timber::GravestoneBehaviour>(), &timber::GravestoneBehaviour::Move);

    player->GetComponent<timber::PlayerBehaviour>()->OnDeathEvent.AddListener(gravestone->GetComponent<timber::GravestoneBehaviour>(), &timber::GravestoneBehaviour::Enable);
    player->GetComponent<timber::PlayerBehaviour>()->OnDeathEvent.AddListener(pauseText->GetComponent<timber::PauseBehaviourText>(), &timber::PauseBehaviourText::OnSquished);
#pragma endregion

#pragma region Commands
    auto& input = InputManager::GetInstance();

    input.BindCommand<timber::Restart>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::R, player);
    input.BindCommand<timber::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Right, player, timber::MovePlayer::Direction::Right);
    input.BindCommand<timber::MovePlayer>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Left, player, timber::MovePlayer::Direction::Left);
    input.BindCommand<timber::Pause>(PlayerIdx::KEYBOARD, KeyState::PRESSED, sf::Keyboard::Scancode::Enter, player);
#pragma endregion
    
}
