#include "InputManager.h"
#include "../Interfaces/IObserver.h"
#include "../Singleton/PauseSingleton.h"

// #include <format>
#include <ranges>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

bool diji::InputManager::ProcessInput()
{
	ResetKeyboardPressedState();

	if (!PollKeyboardEvents())
		return false;
	
	ProcessKeyboardInput();

	return m_Continue;
}

void diji::InputManager::ProcessKeyboardInput()
{
	// std::views::filter([](const auto& pair){ return pair.second; }) filters the map to only include entries where the second element (the boolean value) is true using a predicate lambda.
	for (const auto& [scancode, pressed] : m_KeyPressedState | std::views::filter([](const auto& pair){ return pair.second; }))
	{
		OnKeyEvent(KeyState::PRESSED, scancode);
	}
	for (const auto& [scancode, held] : m_KeyHeldState | std::views::filter([](const auto& pair){ return pair.second; }))
	{
		OnKeyEvent(KeyState::HELD, scancode);
	}
}

void diji::InputManager::ProcessKeyboardStates(const std::optional<sf::Event>& event)
{
	if (!event) return;
	
	if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>())
	{
		const auto& scancode = keyPressedEvent->scancode;
        
		// Check if the key is not already pressed
		if (!m_KeyHeldState[scancode])
			m_KeyPressedState[scancode] = true;
            
		m_KeyHeldState[scancode] = true;
	}
	else if (const auto* keyReleasedEvent = event->getIf<sf::Event::KeyReleased>())
	{
		const auto& scancode = keyReleasedEvent->scancode;
		m_KeyPressedState[scancode] = false;
		m_KeyHeldState[scancode] = false;
	}
}

void diji::InputManager::OnKeyEvent(KeyState state, sf::Keyboard::Scan scancode)
{
	const auto& it = m_CommandUMap.find({state, scancode});
	if (it != m_CommandUMap.end())
	{
		for (const auto& [playerIdx, commandUPtr] : it->second)
		{
			commandUPtr->Execute();
		}
	}
}

void diji::InputManager::ResetKeyboardPressedState()
{
	for (auto& pressed : m_KeyPressedState | std::views::values)
	{
		pressed = false;
	}
}

bool diji::InputManager::PollKeyboardEvents()
{
	while (const std::optional event = m_WindowPtr->pollEvent())
	{
		if (!event) continue;
		
		if (event->is<sf::Event::Closed>())
			return false;
		
		// Set KeyPressed and KeyHeld states
		ProcessKeyboardStates(event);
		
		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				return false;

			// todo: wtf is engine coded pause?
			if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
			{
				PauseSingleton::GetInstance().TogglePause();
				Notify(MessageTypes::GamePaused);
			}
		}
		else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
		{
			OnKeyEvent(KeyState::RELEASED, keyReleased->scancode);
		}

		// if (not m_ControllersIdxs.empty())
		// {
		// 	ProcessControllerInput();
		// }
	}
	
	return true;
}
