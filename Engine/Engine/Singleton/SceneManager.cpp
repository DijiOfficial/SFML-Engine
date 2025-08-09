#include "SceneManager.h"

#include "TimerManager.h"
#include "../Components/Transform.h"

diji::Scene* diji::SceneManager::CreateScene(const int id)
{
    // Check if the scene already exists in the map
    auto it = m_ScenesUPtrMap.find(id);
    if (it != m_ScenesUPtrMap.end())
    {
        // Scene already exists, return the existing scene
        return it->second.get();
    }

    // Scene does not exist, create a new one and store it in the map
    m_ScenesUPtrMap[id] = std::make_unique<Scene>();
    return m_ScenesUPtrMap[id].get();
}

void diji::SceneManager::Init() const
{
    TimerManager::GetInstance().Init();
    m_ScenesUPtrMap.at(m_ActiveSceneId)->Init();
}

void diji::SceneManager::Start() const
{
    m_ScenesUPtrMap.at(m_ActiveSceneId)->Start();
}

void diji::SceneManager::FixedUpdate() const
{
    m_ScenesUPtrMap.at(m_ActiveSceneId)->FixedUpdate();
}

void diji::SceneManager::Update() const
{
    m_ScenesUPtrMap.at(m_ActiveSceneId)->Update();
    TimerManager::GetInstance().Update(); // I'm not sure if it matters where/when this is updated. (before/after comps, late update?)
}

void diji::SceneManager::LateUpdate() const
{
    m_ScenesUPtrMap.at(m_ActiveSceneId)->LateUpdate();
}

void diji::SceneManager::Render()
{
    m_ScenesUPtrMap.at(m_ActiveSceneId)->Render();

    // todo: everything below this should be in a custom function called at the end of the frame. 
    // Everything has been updated and rendered
    // Handle pending destroy
    if (m_HasPendingDestroy)
    {
        // todo: Instead of iterating through all of them and removing them, pass it to the scene so I can use swap method to destroy all of them without having to iterate over all of the game objects multiple time.
        for (const auto gameObject : m_PendingDestroyVec)
        {
            m_ScenesUPtrMap.at(m_ActiveSceneId)->Remove(gameObject);
        }

        m_PendingDestroyVec.clear();
        m_HasPendingDestroy = false;
    }
    
    //  we can load the new scene
    if (m_IsSceneChange) // todo: async new scene loading, ideally this should be its own function after the whole loop
    {
        m_IsSceneChange = false;
        
        // Destroy current scene
       OnDestroy();

        
        m_ActiveSceneId = m_NextScene;
        
        // Load New scene
        m_ScenesUPtrMap.at(m_ActiveSceneId)->Init();
        m_ScenesUPtrMap.at(m_ActiveSceneId)->Start();
    }
}

void diji::SceneManager::OnDestroy() const
{
    m_ScenesUPtrMap.at(m_ActiveSceneId)->OnDestroy();
}

void diji::SceneManager::SetPendingDestroy(GameObject* gameObject)
{
    m_HasPendingDestroy = true;
    m_PendingDestroyVec.push_back(gameObject);
}

diji::GameObject* diji::SceneManager::GetGameObject(const std::string& name) const
{
    return m_ScenesUPtrMap.at(m_ActiveSceneId)->GetGameObject(name);
}

diji::GameObject* diji::SceneManager::SpawnGameObject(const std::string& name, const GameObject* original, const sf::Vector2f& spawnLocation) const
{
    const auto gameObject = m_ScenesUPtrMap.at(m_ActiveSceneId).get()->CreateGameObjectFromTemplate(name, original);

    gameObject->GetComponent<Transform>()->SetPosition(spawnLocation);

    gameObject->Init();
    gameObject->Start();

    return gameObject;
}
