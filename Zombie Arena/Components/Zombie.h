#pragma once
#include "Engine/Components/Component.h"

namespace diji
{
    class TextureComp;
    class Transform;
}

namespace zombieArena
{
    enum class ZombieType
    {
        BLOATER = 0,
        CHASER,
        CRAWLER,
        TOTAL_ZOMBIE_TYPES
    };
    
    class Zombie final : public diji::Component
    {
    public:
        explicit Zombie(diji::GameObject* ownerPtr, const diji::GameObject* target, ZombieType type);
        ~Zombie() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override;
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        [[nodiscard]] bool Hit();
        [[nodiscard]] bool IsDead() const { return m_IsDead; }
        void SetTarget(const diji::GameObject* target) const;
        void SetType(const ZombieType type);

    private:
        // this type of information should be read from a file, for the scope though hell nah
        const float BLOATER_SPEED = 40;
        const float CHASER_SPEED = 80;
        const float CRAWLER_SPEED = 20;

        const int BLOATER_HEALTH = 5;
        const int CHASER_HEALTH = 1;
        const int CRAWLER_HEALTH = 3;
        
        const diji::GameObject* m_PendingTarget = nullptr;
        diji::Transform* m_TransformCompPtr = nullptr;
        diji::TextureComp* m_TextureCompPtr = nullptr;
        ZombieType m_Type = ZombieType::BLOATER;
        int m_Health = 0;
        float m_Speed = 0;
        bool m_IsDead = false;

        void SetZombieStats();
    };
}
