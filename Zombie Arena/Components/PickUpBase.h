#pragma once
#include "Engine/Components/Component.h"

#include <SFML/Graphics/Rect.hpp>

namespace diji
{
    class Transform;
}

// In the case of this game, a PickUpManager with the combined logic of the pickups would have been simpler
namespace zombieArena
{
    class PickUpBase : public diji::Component
    {
    public:
        explicit PickUpBase(diji::GameObject* ownerPtr) : Component(ownerPtr) {}
        explicit PickUpBase(diji::GameObject* ownerPtr, const sf::IntRect& arena);
        ~PickUpBase() noexcept override = default;

        void Init() override;
        void OnEnable() override {}
        void Start() override {}
        
        void Update() override {}
        void FixedUpdate() override {}
        void LateUpdate() override {}

        void OnDisable() override {}
        void OnDestroy() override {}

        void SetValue(const int value) { m_Value = value; }
        void SetArena(const sf::IntRect& arena) { m_Arena = arena; }

        void Spawn() const;

    protected:
        diji::Transform* m_TransformCompPtr = nullptr;
        sf::IntRect m_Arena = {};
        int m_Value = 0;

    private:
        const float LIFETIME = 5.f;
        const float RESPAWN_DELAY = 10;
    };
}
