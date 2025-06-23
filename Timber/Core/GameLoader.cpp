#include "GameLoader.h"

#include <SFML/Graphics/Color.hpp>

#include "GameStates.h"
#include "../Components/Beehaviour.h"
#include "../Components/CloudBehaviour.h"

#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"
#include "Engine/Components/TextComp.h"

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
    scoreCounter->AddComponents<TextComp>("Score = 0", "fonts/KOMIKAP_.ttf", sf::Color::White);
    scoreCounter->GetComponent<TextComp>()->GetText().setCharacterSize(100);
    scoreCounter->AddComponents<Transform>(20, 20);
    scoreCounter->AddComponents<Render>();
    scoreCounter->SetParent(HUD, false);

    const auto pauseText = timberScene->CreateGameObject("pauseTextHUD");
    pauseText->AddComponents<TextComp>("Press Enter to start!", "fonts/KOMIKAP_.ttf", sf::Color::White);
    pauseText->GetComponent<TextComp>()->GetText().setCharacterSize(75);
    pauseText->AddComponents<Transform>(960, 540); // use viewport width/height
    pauseText->AddComponents<Render>();
    pauseText->SetParent(HUD, false);
    
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(timber::GameState::LEVEL));
}
