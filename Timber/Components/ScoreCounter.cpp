#include "ScoreCounter.h"
#include "Engine/Core/GameObject.h"
#include "Engine/Components/TextComp.h"

timber::ScoreCounter::ScoreCounter(diji::GameObject* ownerPtr, const int score)
    : Component(ownerPtr)
    , m_Score{ score }
    , m_TextCompPtr{ nullptr }
{

}

void timber::ScoreCounter::Init()
{
    m_TextCompPtr = GetOwner()->GetComponent<diji::TextComp>();
}

void timber::ScoreCounter::IncreaseScore(bool)
{
    ++m_Score;

    OnScoreIncreasedEvent.Broadcast(m_Score);
    
    const std::string formattedScore = std::format("Score = {}", m_Score);
    m_TextCompPtr->GetText().setString(formattedScore);
}

void timber::ScoreCounter::Reset()
{
    m_Score = -1;
    IncreaseScore();
}
