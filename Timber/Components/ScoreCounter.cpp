#include "ScoreCounter.h"
#include "Engine/Core/GameObject.h"
#include "../Interfaces/Observers.h"
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

void timber::ScoreCounter::IncreaseScore(const int score)
{
    m_Score += score;
    // Notify(static_cast<diji::MessageTypes>(MessageTypesDerived::ScoreChange));

    const std::string formattedScore = std::format("Score = {}", m_Score);
    m_TextCompPtr->GetText().setString(formattedScore);
}

void timber::ScoreCounter::OnNotify(const diji::MessageTypes message)
{
    if (message == static_cast<diji::MessageTypes>(MessageTypesDerived::Restart))
    {
        m_Score = 0;
        IncreaseScore(0);
    }
}

