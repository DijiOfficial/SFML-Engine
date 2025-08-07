#include "BranchBehaviour.h"

#include "PlayerBehaviour.h"
#include "Engine/Components/TextureComp.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Singleton/RandNumber.h"
#include "Engine/Singleton/SceneManager.h"

void timber::BranchBehaviour::Init()
{
    m_TextureCompPtr = GetOwner()->GetComponent<diji::TextureComp>();
    m_TextureCompPtr->SetOrigin(sf::Vector2f{ 220, 20 });
    m_TransformCompPtr = GetOwner()->GetComponent<diji::Transform>();
    

    const auto player = diji::SceneManager::GetInstance().GetGameObject("X_player");
    player->GetComponent<PlayerBehaviour>()->OnPlayerMovedEvent.AddListener(this, &BranchBehaviour::MoveBranch);
    player->GetComponent<PlayerBehaviour>()->OnRestartEvent.AddListener(this, &BranchBehaviour::Reset);

    OnDeathEvent.AddListener(player->GetComponent<PlayerBehaviour>(), &PlayerBehaviour::DeathHandle);
    
    m_Height += 50;
    m_OriginHeight = m_Height;

    Reset();
}

void timber::BranchBehaviour::MoveBranch(const bool isLeft)
{
    m_Height += 150;

    if (m_Height > 850)
    {
        m_Height = 50;
        ChooseRandomSide();
    }

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

    if (m_Height >= 800)
    {
        const BranchSide playerSide = isLeft ? BranchSide::Left : BranchSide::Right;
        if (m_BranchSide == playerSide)
        {
            OnDeathEvent.Broadcast();
        }
    }
}

void timber::BranchBehaviour::ChooseRandomSide()
{
    m_BranchSide = static_cast<BranchSide>(std::min(diji::RandNumber::GetRandomRangeInt(0, 4), 2));
}

void timber::BranchBehaviour::Reset()
{
    m_Height = m_OriginHeight;
    ChooseRandomSide();

    if (m_Height > 350)
        m_BranchSide = BranchSide::None;

    MoveBranch();
}
