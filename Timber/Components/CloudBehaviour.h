#pragma once
#include "Beehaviour.h"

namespace timber
{
    class CloudBehaviour final : public Beehaviour
    {
    public:
        explicit CloudBehaviour(diji::GameObject* ownerPtr, float minHeight, float maxHeight, float minScale);
        ~CloudBehaviour() noexcept override = default;

        void SetHeightVariables(const float minHeight, const float maxHeight) { m_MinHeight = minHeight; m_MaxHeight = maxHeight; }
    };
}

