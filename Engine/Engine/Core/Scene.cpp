#include "Scene.h"

#include <ranges>
#include <stdexcept>

diji::Scene::~Scene() noexcept
{
    m_ObjectsUPtrMap.clear();
};

void diji::Scene::Init()
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->Init();
    }
}

void diji::Scene::Start()
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->Start();
    }
}

void diji::Scene::FixedUpdate()
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->FixedUpdate();
    }
}

void diji::Scene::Update()
{
    for(const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->Update();
    }
}

void diji::Scene::LateUpdate()
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->LateUpdate();
    }
}

void diji::Scene::Render() const
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->Render();
    }
}

void diji::Scene::OnDestroy()
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->OnDisable();
    }
}

diji::GameObject* diji::Scene::CreateGameObject(const std::string& name)
{
    if (m_ObjectsUPtrMap.contains(name))
        throw std::runtime_error("A GameObject with the given name already exists.");
	
    m_ObjectsUPtrMap[name] = std::make_unique<GameObject>();
    return m_ObjectsUPtrMap.at(name).get();
}

void diji::Scene::Remove(const GameObject* object)
{
    for (auto it = m_ObjectsUPtrMap.begin(); it != m_ObjectsUPtrMap.end(); ++it)
    {
        if (it->second.get() == object)
        {
            m_ObjectsUPtrMap.erase(it);
            break;
        }
    }
}

void diji::Scene::Remove(const std::string& name)
{
    auto it = m_ObjectsUPtrMap.find(name);
    if (it != m_ObjectsUPtrMap.end())
    {
        m_ObjectsUPtrMap.erase(it);
    }
}

void diji::Scene::RemoveAll()
{
    m_ObjectsUPtrMap.clear();
}

diji::GameObject* diji::Scene::GetGameObject(const std::string& name) const
{
    const auto it = m_ObjectsUPtrMap.find(name);
	
    return it != m_ObjectsUPtrMap.end() ? it->second.get() : nullptr;
}

std::string diji::Scene::GetGameObjectName(const GameObject* object) const
{
    for (const auto& [name, gameObject] : m_ObjectsUPtrMap)
    {
        if (gameObject.get() == object)
        {
            return name;
        }
    }
    throw std::runtime_error("GameObject not found in the scene.");
}


