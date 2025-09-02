#include "BulletHudDisplay.h"

#include "Engine/Core/GameObject.h"
#include "Engine/Components/TextComp.h"

void zombieArena::BulletHudDisplay::Init()
{
    m_TextCompPtr = GetOwner()->GetComponent<diji::TextComp>();
}

void zombieArena::BulletHudDisplay::UpdateText(const int currentAmmo, const int maxAmmo) const
{
    m_TextCompPtr->GetText().setString(std::format("{}/{}", currentAmmo, maxAmmo));
}
