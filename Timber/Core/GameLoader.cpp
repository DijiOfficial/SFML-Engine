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

    SceneManager::GetInstance().SetActiveScene(static_cast<int>(timber::GameState::LEVEL));
}
