#pragma once
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
    class RenderWindow;
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
        void Init(sf::RenderWindow* window) { m_WindowPtr = window; }
        bool ProcessInput();
        
        template<typename T, typename... Args>
            requires std::derived_from<T, GameActorCommands>
        void BindCommand(const PlayerIdx playerIdx, KeyState state, const Input::InputType input, GameObject* actor, Args... args)
        {
            // if (playerIdx != PlayerIdx::KEYBOARD)
            // {
            //     BindController(static_cast<int>(playerIdx));
            // }

            
            const auto key = std::make_pair(state, std::get<sf::Keyboard::Scan>(input));
    
            m_CommandUMap[key].emplace_back(PlayerCommand{ playerIdx, std::make_unique<T>(actor, std::forward<Args>(args)...)});
        }
        
        void ResetCommands() { m_CommandUMap.clear(); }
        void Quit() { m_Continue = false; }
        
    private:
        bool m_Continue = true;
        struct PlayerCommand
        {
            PlayerIdx playerIndex;
            std::unique_ptr<GameActorCommands> commandUPtr;
        };
		
        std::map<int, std::unique_ptr<Controller>> m_PlayersMap;
        std::vector<int> m_ControllersIdxs;


        // O(1) lookup for commands
        using CommandKey = std::pair<KeyState, sf::Keyboard::Scan>;
        struct CommandKeyHash
        {
            std::size_t operator()(const CommandKey& k) const
            {
                return std::hash<int>()(static_cast<int>(k.first)) ^ (std::hash<int>()(static_cast<int>(k.second)) << 1);
            }
        };
        std::unordered_map<CommandKey, std::vector<PlayerCommand>, CommandKeyHash> m_CommandUMap;
        void OnKeyEvent(KeyState state, sf::Keyboard::Scan scancode);

        // Keyboard state tracking
        sf::RenderWindow* m_WindowPtr = nullptr;
        std::unordered_map<sf::Keyboard::Scancode, bool> m_KeyPressedState;
        std::unordered_map<sf::Keyboard::Scancode, bool> m_KeyHeldState;
        void ProcessKeyboardStates(const std::optional<sf::Event>& event);
        void ResetKeyboardPressedState();

        
        // void ProcessControllerInput();
        void ProcessKeyboardInput();
        [[nodiscard]] bool PollKeyboardEvents();
        // void BindController(int controllerIdx);
    };
}
