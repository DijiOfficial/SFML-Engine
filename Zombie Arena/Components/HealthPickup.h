#pragma once
#include "PickUpBase.h"

namespace zombieArena
{
    class HealthPickup final : public PickUpBase
    {
    public:
        explicit HealthPickup(diji::GameObject* ownerPtr) : PickUpBase(ownerPtr) {}
        explicit HealthPickup(diji::GameObject* ownerPtr, const sf::IntRect& arena) : PickUpBase(ownerPtr, arena) {}
        ~HealthPickup() noexcept override = default;

        void Init() override;
        void PickedUp(const diji::GameObject* player) override;
    };
}