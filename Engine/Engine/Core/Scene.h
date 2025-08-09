#pragma once
#include "GameObject.h"
#include <map>
#include <memory>
#include <string>

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
        GameObject* GetGameObject(const std::string& name) const;
        std::string GetGameObjectName(const GameObject* object) const;
		
    private:
        std::map<std::string, std::unique_ptr<GameObject>> m_ObjectsUPtrMap;
    };
}