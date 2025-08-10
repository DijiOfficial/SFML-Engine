#include "AmmoPickup.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/TextureComp.h"

void zombieArena::AmmoPickup::Init()
{
   PickUpBase::Init();
   
   GetOwner()->GetComponent<diji::TextureComp>()->SetTexture("graphics/ammo_pickup.png");
   GetOwner()->GetComponent<diji::TextureComp>()->SetOriginToCenter();

   m_Value = 12;
}