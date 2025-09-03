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

diji::Engine::Engine(const std::string& dataPath, const std::string& title, const bool useScreenResolution)
{
	window::VIEWPORT = useScreenResolution ? sf::VideoMode::getDesktopMode().size : sf::Vector2u{ 1920, 1080 };
	window::g_window_ptr = std::make_unique<sf::RenderWindow>(sf::VideoMode(window::VIEWPORT), title, sf::Style::Default, sf::State::Fullscreen);

	if (window::g_window_ptr == nullptr)
	{
		throw std::runtime_error(std::string("Create Window Error"));
	}

	Renderer::GetInstance().Init(window::g_window_ptr.get());
	InputManager::GetInstance().Init(window::g_window_ptr.get());
	ResourceManager::GetInstance().Init(dataPath);
}

void diji::Engine::Run(const std::function<void()>& load) const
{
	load();
	
	//Enable vSync
	window::g_window_ptr->setVerticalSyncEnabled(true);

	const auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	const auto& pause = PauseSingleton::GetInstance();

	auto lastFrameTime{ std::chrono::high_resolution_clock::now() };
	float lag = 0.0f;

	sceneManager.Init();
	sceneManager.Start();

	while (window::g_window_ptr->isOpen())
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

		// starting to consider passing the deltaTime to Update methods with [[maybe_unused]] attribute
		// TimeSingleton is useful for other purposes but gets annoying to use in update methods and mostly optimizing the call
		sceneManager.Update();
		sceneManager.LateUpdate();
		
		renderer.Render();
		
		sceneManager.EndFrameUpdate();
	}
	
	window::g_window_ptr->close();
	
	sceneManager.OnDestroy();
}
