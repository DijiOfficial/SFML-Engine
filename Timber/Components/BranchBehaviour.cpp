#include "BranchBehaviour.h"

#include "Engine/Components/TextureComp.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/RandNumber.h"

void timber::BranchBehaviour::Init()
{
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();
    m_TextureCompPtr->SetOrigin(sf::Vector2f{ 220, 20 });
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    ChooseRandomSide();
}

void timber::BranchBehaviour::Update()
{
    switch (m_BranchSide)
    {
    case BranchSide::Left:
        m_TransformCompPtr->SetPosition(610, m_Height);
        m_TextureCompPtr->SetRotationAngle(180);
        break;
    case BranchSide::Right:
        m_TransformCompPtr->SetPosition(1330, m_Height);
        m_TextureCompPtr->SetRotationAngle(0);
        break;
    case BranchSide::None:
        m_TransformCompPtr->SetPosition(3000, m_Height);
        break;
    }
}

void timber::BranchBehaviour::ChooseRandomSide()
{
    m_BranchSide = static_cast<BranchSide>(diji::RandNumber::GetInstance().GetRandomRangeInt(0, 2));
}
