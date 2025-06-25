#include "AxeBehaviour.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"

void timber::AxeBehaviour::Init()
{
    m_Transform = GetOwner()->GetComponent<diji::Transform>();
}

void timber::AxeBehaviour::SetPosition(const bool isLeft)
{
    m_Transform->SetPosition(isLeft ? AXE_POSITION_LEFT : AXE_POSITION_RIGHT, 830);
}

void timber::AxeBehaviour::Reset()
{
    m_Transform->SetPosition(AXE_POSITION_LEFT, 830);
}
