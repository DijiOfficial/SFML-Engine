#include "GameLoader.h"

#include <SFML/Graphics/Color.hpp>

#include "GameStates.h"
#include "../Components/Beehaviour.h"
#include "../Components/CloudBehaviour.h"
#include "../Components/PauseBehaviourText.h"
#include "../Components/ScoreCounter.h"

#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/TextComp.h"
#include "Engine/Input/InputManager.h"

using namespace diji;

void SceneLoader::DefaultCircle()
{
    
}

void SceneLoader::Load()
{
    
}

void SceneLoader::Timber()
{
    const auto& timberScene = SceneManager::GetInstance().CreateScene(static_cast<int>(timber::GameState::LEVEL));
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(timber::GameState::LEVEL));

    const auto background = timberScene->CreateGameObject("BackgroundLevel.png");
    background->AddComponents<TextureComp>("graphics/background.png");
    background->AddComponents<Transform>(0, 0);
    background->AddComponents<Render>();

    const auto tree = timberScene->CreateGameObject("tree");
    tree->AddComponents<TextureComp>("graphics/tree.png");
    tree->AddComponents<Transform>(810, 0);
    tree->AddComponents<Render>();

    const auto bee = timberScene->CreateGameObject("bee");
    bee->AddComponents<TextureComp>("graphics/bee.png");
    bee->AddComponents<Transform>(0, 800);
    bee->AddComponents<Render>();
    bee->AddComponents<timber::Beehaviour>();

    const auto cloud = timberScene->CreateGameObject("cloud");
    cloud->AddComponents<TextureComp>("graphics/cloud.png");
    cloud->AddComponents<Transform>(0, 0);
    cloud->AddComponents<Render>();
    cloud->AddComponents<timber::CloudBehaviour>(0.f, 150.f);
    
    const auto cloud2 = timberScene->CreateGameObject("cloud2", cloud);
    cloud2->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 150);
    
    const auto cloud3 = timberScene->CreateGameObject("cloud3", cloud);
    cloud3->GetComponent<timber::CloudBehaviour>()->SetHeightVariables(-150, 350);

    const auto HUD = timberScene->CreateGameObject("HUD");
    HUD->AddComponents<Transform>(0, 0);

    const auto scoreCounter = timberScene->CreateGameObject("scoreCounterHUD");
    // todo: if we want to decouple more we can inherit from TextComp and create a new comp that listens on ScoreCounter to update itself.
    scoreCounter->AddComponents<TextComp>("Score = 0", "fonts/KOMIKAP_.ttf", sf::Color::White);
    scoreCounter->GetComponent<TextComp>()->GetText().setCharacterSize(100);
    scoreCounter->AddComponents<timber::ScoreCounter>(0);
    scoreCounter->AddComponents<Transform>(20, 20);
    scoreCounter->AddComponents<Render>();
    scoreCounter->SetParent(HUD, false);

    const auto pauseText = timberScene->CreateGameObject("pauseTextHUD");
    pauseText->AddComponents<TextComp>("Press Enter to start!", "fonts/KOMIKAP_.ttf", sf::Color::White, true);
    pauseText->GetComponent<TextComp>()->GetText().setCharacterSize(75);
    pauseText->AddComponents<Transform>(960, 540); // use viewport width/height
    pauseText->AddComponents<timber::PauseBehaviourText>();
    pauseText->AddComponents<Render>();
    pauseText->GetComponent<Render>()->DisableRender();
    pauseText->SetParent(HUD, false);

    
#pragma region Observers
    InputManager::GetInstance().AddObserver(MessageTypes::GamePaused, pauseText->GetComponent<timber::PauseBehaviourText>());
#pragma endregion
    
}
