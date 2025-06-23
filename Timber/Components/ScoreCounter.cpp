#include "ScoreCounter.h"
// #include "Observers.h"
#include "Engine/Core/GameObject.h"
// #include "HealthCounter.h"
// #include "ISoundSystem.h"

timber::ScoreCounter::ScoreCounter(diji::GameObject* ownerPtr, const int score)
    : Component(ownerPtr)
    , m_Score{ score }
{

};

void timber::ScoreCounter::IncreaseScore(const int score)
{
    m_Score += score;
    // Notify(static_cast<diji::MessageTypes>(MessageTypesDerived::SCORE_CHANGE));
}

