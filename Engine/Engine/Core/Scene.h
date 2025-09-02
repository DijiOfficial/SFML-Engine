#pragma once
#include "GameObject.h"
#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/View.hpp>

namespace diji 
{
    class Scene final
    {
    public:
        Scene() = default;
        ~Scene() noexcept;

        Scene(const Scene& other) = delete;
        Scene(Scene&& other) = delete;
        Scene& operator=(const Scene& other) = delete;
        Scene& operator=(Scene&& other) = delete;

        void Init();
        void Start();
        void FixedUpdate();
        void Update();
        void LateUpdate();
        void Render() const;

        void OnDestroy();
		
        [[nodiscard]] GameObject* CreateGameObject(const std::string& name);
        [[nodiscard]] GameObject* CreateGameObject(const std::string& name, const GameObject* original);
        [[nodiscard]] GameObject* CreateGameObjectFromTemplate(const std::string& name, const GameObject* original);
        void Remove(const GameObject* object);
        void Remove(const std::string& name);
        void RemoveAll();
        [[nodiscard]] GameObject* GetGameObject(const std::string& name) const;
        std::string GetGameObjectName(const GameObject* object) const;

        void SetGameObjectAsCanvasObject(const std::string& name);
        void SetGameObjectAsCanvasObject(const GameObject* object);
        void SetCanvasView(const sf::View& view) { m_CanvasView = view; }
		
    private:
        std::map<std::string, std::unique_ptr<GameObject>> m_ObjectsUPtrMap;
        std::map<std::string, std::unique_ptr<GameObject>> m_CanvasObjectsUPtrMap;
        sf::View m_CanvasView = sf::View(sf::Vector2f{ 1920 * 0.5f, 1080 * 0.5f }, sf::Vector2f{ 1920, 1080 });
    };
}
