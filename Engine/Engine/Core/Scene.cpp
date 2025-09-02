#include "Scene.h"

#include <ranges>
#include <stdexcept>

#include "Engine.h"

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

    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
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

    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
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

    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
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

    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
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

    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
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

    window::g_window_ptr->setView(m_CanvasView);
    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
    {
        gameObject->Render();
    }
}

void diji::Scene::OnDestroy()
{
    for (const auto& gameObject : m_ObjectsUPtrMap | std::views::values)
    {
        gameObject->OnDestroy();
    }

    for (const auto& gameObject : m_CanvasObjectsUPtrMap | std::views::values)
    {
        gameObject->OnDestroy();
    }

    m_ObjectsUPtrMap.clear();
    m_CanvasObjectsUPtrMap.clear();
}

diji::GameObject* diji::Scene::CreateGameObject(const std::string& name)
{
    if (m_ObjectsUPtrMap.contains(name))
        throw std::runtime_error("A GameObject with the given name already exists.");
	
    m_ObjectsUPtrMap[name] = std::make_unique<GameObject>();
    return m_ObjectsUPtrMap.at(name).get();
}

diji::GameObject* diji::Scene::CreateGameObject(const std::string& name, const GameObject* original)
{
    if (m_ObjectsUPtrMap.contains(name))
        throw std::runtime_error("A GameObject with the given name already exists.");

    m_ObjectsUPtrMap[name] = std::make_unique<GameObject>();
    original->CreateDuplicate(m_ObjectsUPtrMap.at(name).get());
    return m_ObjectsUPtrMap.at(name).get();
}

diji::GameObject* diji::Scene::CreateGameObjectFromTemplate(const std::string& name, const GameObject* original)
{
    std::string finalName = name;

    // Check if name already exists, if it does get the suffix and increment it until you get new name
    // todo: Likely some optimization can be done here. Like keeping track of the last used suffix or internal counter or ...
    while (m_ObjectsUPtrMap.contains(finalName))
    {
        // Find numeric suffix
        size_t pos = finalName.size();
        while (pos > 0 && std::isdigit(static_cast<unsigned char>(finalName[pos - 1])))
            --pos;

        if (pos == finalName.size()) // No number suffix so append 0
        {
            finalName += "0";
        }
        else
        {
            // Increment existing number suffix
            std::string namePart = finalName.substr(0, pos);
            const int number = std::stoi(finalName.substr(pos));
            finalName = namePart + std::to_string(number + 1);
        }
    }

    m_ObjectsUPtrMap[finalName] = std::make_unique<GameObject>();
    original->CreateDuplicate(m_ObjectsUPtrMap[finalName].get());

    return m_ObjectsUPtrMap[finalName].get();
}

void diji::Scene::Remove(const GameObject* object)
{
    object->OnDestroy();
    
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

void diji::Scene::SetGameObjectAsCanvasObject(const std::string& name)
{
    const auto it = m_ObjectsUPtrMap.find(name);
    if (it != m_ObjectsUPtrMap.end())
    {
        // Move the GameObject to m_CanvasObjectsUPtrMap
        m_CanvasObjectsUPtrMap[name] = std::move(it->second);
        m_ObjectsUPtrMap.erase(it);
    }
    else
        throw std::runtime_error("GameObject with the given name does not exist in the scene.");
}

void diji::Scene::SetGameObjectAsCanvasObject(const GameObject* object)
{
    for (auto it = m_ObjectsUPtrMap.begin(); it != m_ObjectsUPtrMap.end(); ++it)
    {
        if (it->second.get() == object)
        {
            // Move the GameObject to m_CanvasObjectsUPtrMap
            m_CanvasObjectsUPtrMap[it->first] = std::move(it->second);
            m_ObjectsUPtrMap.erase(it);
            return;
        }
    }

    throw std::runtime_error("GameObject does not exist in the scene.");
}
