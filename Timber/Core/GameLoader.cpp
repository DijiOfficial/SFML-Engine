#include "GameLoader.h"

#include <SFML/Graphics/Color.hpp>

#include "GameStates.h"
#include "../Components/Beehaviour.h"
#include "../Components/CloudBehaviour.h"
#include "../Components/PauseBehaviourText.h"
#include "../Components/PlayerBehaviour.h"
#include "../Components/ScoreCounter.h"
#include "../Components/TimeBar.h"
#include "../Inputs/CustomCommands.h"
#include "../Interfaces/Observers.h"
#include "Engine/Components/RectRender.h"

#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Input/InputManager.h"

using namespace diji;

void SceneLoader::Timber()
{
    const auto& timberScene = SceneManager::GetInstance().CreateScene(static_cast<int>(timber::GameState::Level));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(timber::GameState::Level));

    const auto background = timberScene->CreateGameObject("A_BackgroundLevel.png");
    background->AddComponents<TextureComp>("graphics/background.png");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<Render>();

    const auto tree = timberScene->CreateGameObject("D_tree");
    tree->AddComponents<TextureComp>("graphics/tree.png");
    tree->AddComponents<Transform>(810, 0);
    tree->AddComponents<Render>();

    const auto bee = timberScene->CreateGameObject("B_bee");
    bee->AddComponents<TextureComp>("graphics/bee.png");
    bee->AddComponents<Transform>(0, 800);
    bee->AddComponents<Render>();
    bee->AddComponents<timber::Beehaviour>();

    const auto cloud = timberScene->CreateGameObject("C_cloud");
    cloud->AddComponents<TextureComp>("graphics/cloud.png");
    cloud->AddComponents<Transform>(0, 0);
    cloud->AddComponents<Render>();
    cloud->AddComponents<timber::CloudBehaviour>(0.f, 150.f);
    
    const auto cloud2 = timberScene->CreateGameObject("C_cloud2", cloud);
    cloud2->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 150);
    
    const auto cloud3 = timberScene->CreateGameObject("C_cloud3", cloud);
    cloud3->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 350);

    const auto HUD = timberScene->CreateGameObject("Z_HUD");
    HUD->AddComponents<Transform>(0, 0);

    const auto scoreCounter = timberScene->CreateGameObject("Z_scoreCounterHUD");
    // todo: if we want to decouple more we can inherit from TextComp and create a new comp that listens on ScoreCounter to update itself.
    scoreCounter->AddComponents<TextComp>("Score = 0", "fonts/KOMIKAP_.ttf", sf::Color::White);
    scoreCounter->GetComponent<TextComp>()->GetText().setCharacterSize(100);
    scoreCounter->AddComponents<timber::ScoreCounter>(0);
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
    timeBar->AddComponents<Transform>(760, 540); // This is useless but I have not tested if it works without
    timeBar->AddComponents<RectRender>();
    
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f{400 , 80});
    rect.setPosition(sf::Vector2f{760, 980});

    timeBar->GetComponent<RectRender>()->SetRectangle(rect);
    timeBar->GetComponent<RectRender>()->SetFillColor(sf::Color::Red);
    timeBar->GetComponent<RectRender>()->SetLineWidth(0.f);
    timeBar->AddComponents<timber::TimeBar>();
    timeBar->SetParent(HUD, false);


    const auto player = timberScene->CreateGameObject("Z_player");
    player->AddComponents<timber::PlayerBehaviour>();

#pragma region Observers
    InputManager::GetInstance().AddObserver(MessageTypes::GamePaused, pauseText->GetComponent<timber::PauseBehaviourText>());
    timeBar->GetComponent<timber::TimeBar>()->AddObserver(static_cast<MessageTypes>(timber::MessageTypesDerived::GameOver), pauseText->GetComponent<timber::PauseBehaviourText>());

    player->GetComponent<timber::PlayerBehaviour>()->AddObserver(static_cast<MessageTypes>(timber::MessageTypesDerived::Restart), timeBar->GetComponent<timber::TimeBar>());
    player->GetComponent<timber::PlayerBehaviour>()->AddObserver(static_cast<MessageTypes>(timber::MessageTypesDerived::Restart), scoreCounter->GetComponent<timber::ScoreCounter>());
    player->GetComponent<timber::PlayerBehaviour>()->AddObserver(static_cast<MessageTypes>(timber::MessageTypesDerived::Restart), pauseText->GetComponent<timber::PauseBehaviourText>());
#pragma endregion

#pragma region Commands
    auto& input = InputManager::GetInstance();

    // todo: fix the input manager.
    input.BindCommand<timber::Restart>(PlayerIdx::KEYBOARD, KeyState::HELD, sf::Keyboard::Scancode::R, player);
#pragma endregion
    
}
