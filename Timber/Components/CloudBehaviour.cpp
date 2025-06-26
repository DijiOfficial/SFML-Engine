#include "CloudBehaviour.h"

timber::CloudBehaviour::CloudBehaviour(diji::GameObject* ownerPtr, const float minHeight, const float maxHeight, const float minScale)
    : Beehaviour(ownerPtr)
{
    m_MinSpeed = 1;
    m_MaxSpeed = 200;
    m_MinHeight = minHeight;
    m_MaxHeight = maxHeight;
    m_StartPosition = -200;
    m_SpeedModifier = 1;
    m_MinSize = minScale;
    m_ClassType = ClassType::Cloud;
}
