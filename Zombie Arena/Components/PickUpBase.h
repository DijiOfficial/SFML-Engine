#pragma once
#include <string>

#include "Engine/Components/Component.h"

#include <SFML/Graphics/Rect.hpp>

namespace diji
{
    class Transform;
    class Collider;
}

// In the case of this game, a PickUpManager with the combined logic of the pickups would have been simpler
namespace zombieArena
{
    enum class PickUpType
    {
        NONE = -1,
        HEALTH,
        AMMO
    };
    
    class PickUpBase : public diji::Component
    {
    public:
        explicit PickUpBase(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        explicit PickUpBase(diji::GameObject* ownerPtr, const sf::IntRect& arena, std::string texturePath);
        explicit PickUpBase(diji::GameObject* ownerPtr, const sf::IntRect& arena, std::string texturePath, PickUpType type, int value);
        ~PickUpBase() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override;
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void SetValue(const int value) { m_Value = value; }
        void SetArena(const sf::IntRect& arena) { m_Arena = arena; }
        void SetTexturePath(const std::string& texturePath) { m_TexturePath = texturePath; }
        void SetPickUpType(const PickUpType type) { m_Type = type; }

        void Spawn() const;

    protected:
        diji::Collider* m_ColliderCompPtr = nullptr;
        diji::Transform* m_TransformCompPtr = nullptr;
        PickUpType m_Type = PickUpType::NONE;
        std::string m_TexturePath;
        sf::IntRect m_Arena = {};
        int m_Value = 0;
    };
}
