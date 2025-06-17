#pragma once

namespace diji
{
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject() noexcept = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		// void Update();
		// void FixedUpdate();
		// void Init();
		// void Render() const;
		// void LateUpdate();
	};
}