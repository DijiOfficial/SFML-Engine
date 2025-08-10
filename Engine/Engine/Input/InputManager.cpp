#include "InputManager.h"

#include <ranges>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

bool diji::InputManager::ProcessInput()
{
	ResetPressedStates();

	if (!PollEvents())
		return false;
	
	ProcessAllInputMaps();
	
	return m_Continue;
}

void diji::InputManager::ResetPressedStates()
{
	for (auto& pressed : m_KeyPressedState | std::views::values)
	{
		pressed = false;
	}

	for (auto& pressed : m_MousePressedState | std::views::values)
	{
		pressed = false;
	}
}

bool diji::InputManager::PollEvents()
{
	while (const std::optional event = m_WindowPtr->pollEvent())
	{
		if (!event) continue;
		
		if (event->is<sf::Event::Closed>())
			return false;
		
		if (const auto keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				return false;
		}

		if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
		{
			m_MousePosition = mouseMoved->position;
			for (auto& command : m_MouseMoveCommandsVec)
			{
				if (command)
					command->Execute(mouseMoved->position);
			}
		}
		
		// Set KeyPressed and KeyHeld states
		SetInputState<sf::Mouse::Button, sf::Event::MouseButtonPressed, sf::Event::MouseButtonReleased>(event, m_MousePressedState, m_MouseHeldState,&sf::Event::MouseButtonPressed::button, &sf::Event::MouseButtonReleased::button);
		SetInputState<sf::Keyboard::Scancode, sf::Event::KeyPressed, sf::Event::KeyReleased>(event, m_KeyPressedState, m_KeyHeldState, &sf::Event::KeyPressed::scancode, &sf::Event::KeyReleased::scancode);

		// Handle release input logic
		auto HandleKeyReleaseEvent = [&](KeyState state, auto* inputEvent, auto eventType)
		{
			if (inputEvent)
				HandleInput(state, eventType(*inputEvent));
		};
		HandleKeyReleaseEvent(KeyState::RELEASED, event->getIf<sf::Event::KeyReleased>(), [](const auto& e) { return e.scancode; });
		HandleKeyReleaseEvent(KeyState::RELEASED, event->getIf<sf::Event::MouseButtonReleased>(), [](const auto& e) { return e.button; });

		// if (not m_ControllersIdxs.empty())
		// {
		// 	ProcessControllerInput();
		// }
	}
	
	return true;
}

void diji::InputManager::ProcessAllInputMaps()
{
	ProcessInputMap(m_KeyPressedState, m_KeyHeldState);
	ProcessInputMap(m_MousePressedState, m_MouseHeldState);
	// add controller
}
