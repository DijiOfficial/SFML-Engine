#include "GameLoader.h"
#include "GameStates.h"

#include "Engine/Singleton/SceneManager.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/Render.h"

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

    const auto bee2 = timberScene->CreateGameObject("bee2", bee);
    bee2->GetComponent<Transform>()->SetPosition(200, 800);
    
    SceneManager::GetInstance().SetActiveScene(static_cast<int>(timber::GameState::LEVEL));
}
