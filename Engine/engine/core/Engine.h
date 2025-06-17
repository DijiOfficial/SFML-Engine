#pragma once
#include <string>
#include <functional>

namespace diji
{
	class Engine final
	{
	public:
		explicit Engine(const std::string& dataPath);
		~Engine() noexcept;

		Engine(const Engine& other) = delete;
		Engine(Engine&& other) = delete;
		Engine& operator=(const Engine& other) = delete;
		Engine& operator=(Engine&& other) = delete;

		void Run(const std::function<void()>& load) const;

	private:
		static constexpr float FIXED_TIME_STEP{ 1 / 60.f };
		//static constexpr float FIXED_TIME_STEP{ 1 / 151.5f };
	};
}
