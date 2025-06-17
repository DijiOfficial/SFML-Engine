#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SFML/Graphics.hpp>

#include "Engine.h"
#include "../input/InputManager.h"
//#include "SceneManager.h"
// #include "Renderer.h"
//#include "ResourceManager.h"
//#include "TimeSingleton.h"
//#include <thread>
//#include "GUI.h"

namespace
{
	std::unique_ptr<sf::RenderWindow> g_window_ptr{};
}

diji::Engine::Engine(const std::string& dataPath)
{
	(void)dataPath;

	g_window_ptr = std::make_unique<sf::RenderWindow>(sf::VideoMode({ 1920, 1080 }), "Timber!!!", sf::Style::Default, sf::State::Fullscreen);

	if (g_window_ptr == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error"));
	}

	//ResourceManager::GetInstance().Init(dataPath);
}

diji::Engine::~Engine() noexcept
{
	g_window_ptr = nullptr; // Not necessary just making sure
}

void diji::Engine::Run(const std::function<void()>& load) const
{
	(void)load;

	//load();
	////Enable vSync
	//SDL_GL_SetSwapInterval(1);

	// const auto& renderer = Renderer::GetInstance();
	//auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	auto lastFrameTime{ std::chrono::high_resolution_clock::now() };
	float lag = 0.0f;

	//sceneManager.Init();

	while (g_window_ptr->isOpen())
	{
		const auto currentTime{ std::chrono::high_resolution_clock::now() };
		const float deltaTime{ std::chrono::duration<float>(currentTime - lastFrameTime).count() };
		lastFrameTime = currentTime;
		lag += deltaTime;

		// TimeSingleton::GetInstance().SetDeltaTime(deltaTime);
		while (const std::optional event = g_window_ptr->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				g_window_ptr->close();

			if (not input.ProcessInput(event))
				g_window_ptr->close();
		}

		// while (lag >= FIXED_TIME_STEP)
		// {
		// 	sceneManager.FixedUpdate();
		// 	lag -= FIXED_TIME_STEP;
		// }

		//	sceneManager.Update();
		//	sceneManager.LateUpdate();
		
		g_window_ptr->clear();
		// renderer.Render();
		g_window_ptr->display();
	}
}
