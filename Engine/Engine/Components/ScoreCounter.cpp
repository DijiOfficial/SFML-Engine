#include "ScoreCounter.h"
#include "../Core/GameObject.h"
#include "TextComp.h"

diji::ScoreCounter::ScoreCounter(GameObject* ownerPtr, const int score)
    : Component(ownerPtr)
    , m_Score{ score }
, m_TextCompPtr{ nullptr }
{

}

void diji::ScoreCounter::Init()
{
    m_TextCompPtr = GetOwner()->GetComponent<TextComp>();
}

void diji::ScoreCounter::IncreaseScore(bool)
{
    ++m_Score;

    OnScoreIncreasedEvent.Broadcast(m_Score);

    const std::string newScore = m_StringScore + std::to_string(m_Score);
    m_TextCompPtr->GetText().setString(newScore);
}

void diji::ScoreCounter::Reset()
{
    m_Score = -1;
    IncreaseScore();
}
