﻿#pragma once
#include "Engine/Components/Component.h"

#include <memory>
#include <SFML/System/Vector2.hpp>

namespace diji
{
    class Transform;
}

namespace zombieArena
{
    // there is only one weapon so it has no inheritance hierarchy, otherwise use a base weapon class
    class Pistol final : public diji::Component
    {
    public:
        explicit Pistol(diji::GameObject* ownerPtr);
        explicit Pistol(diji::GameObject* ownerPtr, float fireRate, int magCapacity);
        ~Pistol() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void UpdatePosition(const sf::Vector2f& pos) const;

        void SetFireRate(const float fireRate) { m_FireRate = fireRate; }
        void SetMagCapacity(const int magCapacity) { m_MagCapacity = magCapacity; }
        
        // FireWeapon -> HandleWeaponFired (check mag, handleshot, play sound, VFX)
        void FireWeapon(bool isStart, const sf::Vector2f& direction);
        
    private:
        std::unique_ptr<diji::GameObject> m_BulletTemplate = nullptr;
        diji::Transform* m_TransformCompPtr = nullptr;
        int m_MagCapacity = 0;
        float m_FireRate = 0.5f;
        bool m_CanShoot = true;

        void HandleWeaponFired(const sf::Vector2f& direction);
        void HandleShot(const sf::Vector2f& direction);
    };
}
