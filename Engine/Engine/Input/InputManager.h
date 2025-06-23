﻿#pragma once
#include "../Singleton/Singleton.h"
#include "Controller.h"
#include "GameActorCommand.h"
// #include "GameObject.h"
//
#include <map>
#include <optional>
#include <variant>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

#include "../Interfaces/Subject.h"

namespace sf
{
    class Event;
}

namespace diji
{
    enum class KeyState
    {
        PRESSED,
        RELEASED,
        HELD,
    };

    // todo: make this variable/editable
    enum class PlayerIdx
    {
        KEYBOARD = -1,
        PLAYER1,
        PLAYER2,
        PLAYER3,
        PLAYER4,
    };
    
    class Input final
    {
    public:
        typedef std::variant<sf::Keyboard::Scancode, Controller::Button> InputType;

        explicit Input(const InputType input)
            : m_Input{ input }
        {
        }
        ~Input() = default;

        Input(const Input& other) = default;
        Input(Input&& other) noexcept = default;
        Input& operator=(const Input& other) = delete;
        Input& operator=(Input&& other) noexcept = delete;

        InputType GetInput() const { return m_Input; }

    private:
        InputType m_Input;
    };

    class InputManager final : public Singleton<InputManager>, public Subject
    {
    public:
        bool ProcessInput(const std::optional<sf::Event>& event, bool& isPaused);
        template<typename T, typename... Args>
            requires std::derived_from<T, GameActorCommands>
        void BindCommand(const PlayerIdx playerIdx, KeyState state, const Input::InputType input, GameObject* actor, Args... args)
        {
            // if (playerIdx != PlayerIdx::KEYBOARD)
            // {
            //     BindController(static_cast<int>(playerIdx));
            // }
            m_CommandsUPtrMap.emplace(state, std::make_pair(Input(input), PlayerCommand{ playerIdx, std::make_unique<T>(actor, std::forward<Args>(args)...) }));
        }
        void ResetCommands() { m_CommandsUPtrMap.clear(); }
        void Quit() { m_Continue = false; }
        
    private:
        bool m_Continue = true;
        struct PlayerCommand
        {
            PlayerIdx playerIndex;
            std::unique_ptr<GameActorCommands> commandUPtr;
        };
        std::unordered_multimap<KeyState, std::pair<Input, PlayerCommand>> m_CommandsUPtrMap;
		
        std::map<int, std::unique_ptr<Controller>> m_PlayersMap;
        std::vector<int> m_ControllersIdxs;

        // void ProcessControllerInput();
        // void ProcessKeyboardInput();
        void ProcessKeyboardInput(const sf::Event::KeyPressed* keyPressed);

        // void BindController(int controllerIdx);
    };
}
