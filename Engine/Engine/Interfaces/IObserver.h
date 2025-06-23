#pragma once

namespace diji 
{
    enum class MessageTypes
    {
        GamePaused = -1
    };

    class Subject;

    class IObserver
    {
    public:
        IObserver() = default;
        virtual ~IObserver() noexcept = default;

        IObserver(const IObserver& other) = delete;
        IObserver(IObserver&& other) = delete;
        IObserver& operator=(const IObserver& other) = delete;
        IObserver& operator=(IObserver&& other) = delete;

        // Message is necessary as an observer can observe multiple subjects and doesn't differentiate between the notifies (ideally doing something like Unreal where the Notify calls a function)
        virtual void OnNotify(MessageTypes message) = 0;
    };
}