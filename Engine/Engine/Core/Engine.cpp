// #define WIN32_LEAN_AND_MEAN 
// #include <windows.h>

#include "Engine.h"
#include "Renderer.h"
#include "../Input/InputManager.h"
#include "../Singleton/SceneManager.h"
#include "../Singleton/ResourceManager.h"
#include "../Singleton/Singleton.h"
#include "../Singleton/TimeSingleton.h"
#include "../Singleton/PauseSingleton.h"

//#include <thread>
#include <SFML/Graphics.hpp>
#include <stdexcept>

namespace
{
	std::unique_ptr<sf::RenderWindow> g_window_ptr{};
	constexpr static sf::Vector2u VIEWPORT{ 1920, 1080 };
}

diji::Engine::Engine(const std::string& dataPath)
{
	g_window_ptr = std::make_unique<sf::RenderWindow>(sf::VideoMode(VIEWPORT), "Timber!!!", sf::Style::Default, sf::State::Fullscreen);

	if (g_window_ptr == nullptr)
	{
		throw std::runtime_error(std::string("Create Window Error"));
	}

	Renderer::GetInstance().Init(g_window_ptr.get());
	InputManager::GetInstance().Init(g_window_ptr.get());
	ResourceManager::GetInstance().Init(dataPath);
}

void diji::Engine::Run(const std::function<void()>& load) const
{
	load();
	
	//Enable vSync
	g_window_ptr->setVerticalSyncEnabled(true);

	const auto& renderer = Renderer::GetInstance();
	const auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	const auto& pause = PauseSingleton::GetInstance();

	auto lastFrameTime{ std::chrono::high_resolution_clock::now() };
	float lag = 0.0f;

	sceneManager.Init();
	sceneManager.Start();

	while (g_window_ptr->isOpen())
	{
		const auto currentTime{ std::chrono::high_resolution_clock::now() };
		const float deltaTime{ std::chrono::duration<float>(currentTime - lastFrameTime).count() };
		lastFrameTime = currentTime;
		lag += deltaTime;

		TimeSingleton::GetInstance().SetDeltaTime(deltaTime);
		if (!input.ProcessInput())
			break;
		
		if (pause.GetIsPaused())
		{
			renderer.Render();
			continue;
		}

		while (lag >= FIXED_TIME_STEP)
		{
			sceneManager.FixedUpdate();
			lag -= FIXED_TIME_STEP;
		}

		sceneManager.Update();
		sceneManager.LateUpdate();
		
		renderer.Render();
	}
	
	g_window_ptr->close();
	
	sceneManager.OnDestroy();
}
