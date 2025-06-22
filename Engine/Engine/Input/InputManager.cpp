#include "InputManager.h"

// #include <format>
#include <SFML/Window/Event.hpp>

bool diji::InputManager::ProcessInput(const std::optional<sf::Event>& event, bool& isPaused)
{
	if (!event) return m_Continue; // this should never trigger

	//todo: change keyPressed to keyHeld and add logic for actual keyPressed
	if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) return false;
		if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) isPaused = !isPaused;
		ProcessKeyboardInput(keyPressed);
	}
	else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
	{
		// Process key stopped
	}


	// if (not m_ControllersIdxs.empty())
	// {
	// 	ProcessControllerInput();
	// }

	return m_Continue;
}

void diji::InputManager::ProcessKeyboardInput(const sf::Event::KeyPressed* keyPressed)
{
	//todo: try using find instead of custom loop?
	for (const auto& [keyState, inputCommandPair] : m_CommandsUPtrMap)
	{
		if (keyState != KeyState::HELD)
			continue;

		const auto& inputType = inputCommandPair.first.GetInput();

		// Check if inputType holds Scancode
		if (std::holds_alternative<sf::Keyboard::Scan>(inputType))
		{
			// Get the Scancode from the variant
			const auto& scancode = std::get<sf::Keyboard::Scan>(inputType);
			if (scancode == keyPressed->scancode)
			{
				inputCommandPair.second.commandUPtr->Execute();
			}
		}
	}
}