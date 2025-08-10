#include "HealthPickup.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/TextureComp.h"

void zombieArena::HealthPickup::Init()
{
    PickUpBase::Init();
    
    GetOwner()->GetComponent<diji::TextureComp>()->SetTexture("graphics/health_pickup.png");
    GetOwner()->GetComponent<diji::TextureComp>()->SetOriginToCenter();

    m_Value = 50;
}
