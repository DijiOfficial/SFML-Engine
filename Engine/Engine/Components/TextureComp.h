﻿#pragma once
#include "Component.h"
#include <string>
#include <SFML/Graphics/Texture.hpp> // can I remove this?

namespace sf
{
	class Texture;
	class Angle;
}

namespace diji
{
	class GameObject;

	// todo if render is different from component then this should inherit from that
	class TextureComp final : public Component
	{
	public:
		explicit TextureComp(GameObject* ownerPtr);
		TextureComp(GameObject* ownerPtr, std::string filename);
		TextureComp(GameObject* ownerPtr, std::string filename, float scaleX, float scaleY);
		TextureComp(GameObject* ownerPtr, std::string filename, float scale);
		~TextureComp() noexcept override = default;

		TextureComp(const TextureComp& other) = delete;
		TextureComp(TextureComp&& other) = delete;
		TextureComp& operator=(const TextureComp& other) = delete;
		TextureComp& operator=(TextureComp&& other) = delete;

		void Init() override;
		void OnEnable() override {}
		void Start() override {}
		
		void FixedUpdate() override {}
		void Update() override {}
		void LateUpdate() override {}

		void OnDisable() override {}
		void OnDestroy() override {}

		void SetTexture(const std::string& filename);
		sf::Texture GetTexture() const { return m_SFMLTexture; }

		void SetScaleX(float scaleX);
		void SetScaleY(float scaleY);
		void SetScale(float scale);
		void SetWidth(int width);
		void SetHeight(int height);
		void SetCanRotate(const bool canRotate) { m_CanRotate = canRotate; }
		void SetRotationAngle(const sf::Angle angle) { m_RotationAngle = angle; }

		int GetWidth() const;
		int GetHeight() const;
		float GetScaleX() const { return m_ScaleX; }
		float GetScaleY() const { return m_ScaleY; }
		sf::Angle GetRotationAngle() const { return m_RotationAngle; }
		bool CanRotate() const { return  m_CanRotate; }

	private:
		sf::Texture m_SFMLTexture;
		std::string m_FilePath;
		
		sf::Angle m_RotationAngle;
		float m_ScaleX = 1;
		float m_ScaleY = 1;
		bool m_CanRotate = false;
	};
}

