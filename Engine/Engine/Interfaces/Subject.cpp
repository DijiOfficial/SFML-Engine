#include "Subject.h"
#include "IObserver.h"

void diji::Subject::AddObserver(const MessageTypes message, IObserver* observer)
{
    //assert(observer && "GameObject must have observer Component");
    const auto it = m_ObserversMap.find(message);
    if (it == m_ObserversMap.end())
        m_ObserversMap[message] = ObserverPtrList();
	
    m_ObserversMap[message].push_front(observer);
}

void diji::Subject::RemoveObserver(const MessageTypes message, IObserver* observer)
{
    const auto it = m_ObserversMap.find(message);

    if (it != m_ObserversMap.end())
    {
        auto& list = it->second;
        list.remove_if([&observer](const IObserver* ptr)
        {
            return ptr == observer;
        });
    }
}

void diji::Subject::Notify(const MessageTypes message)
{
    for (const auto& observer : m_ObserversMap[message])
        observer->OnNotify(message);
}