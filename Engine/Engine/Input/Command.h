#pragma once
namespace diji
{
    class Command
    {
    public:
        Command() = default;
        virtual ~Command() noexcept = default;

        Command(const Command& other) = delete;
        Command(Command&& other) = delete;
        Command& operator=(const Command& other) = delete;
        Command& operator=(Command&& other) = delete;

        virtual void Execute() = 0;
    };
}