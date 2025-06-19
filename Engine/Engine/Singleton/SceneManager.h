#pragma once
#include "Singleton.h"
#include "../Core/Scene.h"

namespace diji
{
    class SceneManager final : public Singleton<SceneManager>
    {
    public:
        Scene* CreateScene(int id);

        // Similar loop to Unity

        // Initialization phase
        void Init() const;          // 1st
        void Start() const;         // 2nd

        // Game loop
        void FixedUpdate() const;   // 3rd
        void Update() const;        // 4th
        void LateUpdate() const;    // 5th
        void Render();              // 6th

        // Destroy Phase
        void OnDestroy() const;     // 6th

        void SetActiveScene(const int id) { m_ActiveSceneId = id; m_NextScene = id; }
        void SetNextSceneToActivate(const int id) { m_NextScene = id; m_IsSceneChange = true; }
        int GetActiveSceneId() const { return m_ActiveSceneId; }
		
    private:
        std::map<int, std::unique_ptr<Scene>> m_ScenesUPtrMap;
        int m_ActiveSceneId = 0;
        int m_NextScene = 0;
        bool m_IsSceneChange = false;
    };
}