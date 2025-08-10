#pragma once
#include "PickUpBase.h"

namespace zombieArena
{
    class AmmoPickup final : public PickUpBase
    {
    public:
        explicit AmmoPickup(diji::GameObject* ownerPtr) : PickUpBase(ownerPtr) {}
        explicit AmmoPickup(diji::GameObject* ownerPtr, const sf::IntRect& arena) : PickUpBase(ownerPtr, arena) {}
        ~AmmoPickup() noexcept override = default;

        void Init() override;
    };
}
