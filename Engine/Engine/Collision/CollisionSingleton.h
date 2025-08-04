﻿#pragma once
#include "../Singleton/Singleton.h"
#include <map>
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

namespace diji
{
	class Collider;

	struct Rectf
	{
		float left, bottom, width, height;
	};

	// Todo: Change collision to Unreal System, Colliders are automatically added and compared for collisions with overlap events?
	// with collision channels for optimization?
	class CollisionSingleton final : public Singleton<CollisionSingleton>
	{
	public:
		void Reset();
		// bool ParseLevelSVG(const std::string& file, const int yAdjust);
		// bool ParseIntersectionsSVG(const std::string& file, const int yAdjust);
		
		void AddCollider(const Collider* object, const Rectf& collider);
		void RemoveCollider(const Collider* object);

		void UpdateCollider(const Collider* object, const Rectf& collider);

		[[nodiscard]] std::vector<const Collider*> IsColliding(const Collider* object);
		[[nodiscard]] bool AreColliding(const Collider* source, const Collider* target);
		[[nodiscard]] bool IsCollidingWithWorld(const Rectf& shape) const;
		[[nodiscard]] bool IsCollidingWithWorld(const sf::Vector2f& point1, const sf::Vector2f& point2) const;
		//temp
		[[nodiscard]] std::vector<std::vector<sf::Vector2f>> GetLevelCollider() const { return m_LevelCollider; }

	private:
		std::map<const Collider*, Rectf> m_Colliders;
		std::vector<std::vector<sf::Vector2f>> m_LevelCollider;

		[[nodiscard]] float Distance(const sf::Vector2f& a, const sf::Vector2f& b) const;
		[[nodiscard]] float DistanceSquared(const sf::Vector2f& a, const sf::Vector2f& b) const;
		
		// taken from Prog2 Engine credits to Koen Samyn
		[[nodiscard]] bool Raycast(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& rayP1, const sf::Vector2f& rayP2) const;
		[[nodiscard]] bool Raycast(const sf::Vector2f* vertices, const size_t nrVertices, const sf::Vector2f& rayP1, const sf::Vector2f& rayP2) const;
		[[nodiscard]] bool IntersectLineSegments(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2, float& outLambda1, float& outLambda2, double epsilon = 1e-6) const;
		[[nodiscard]] bool IsPointOnLineSegment(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b) const;
		[[nodiscard]] bool AreRectsColliding(const Rectf& rect1, const Rectf& rect2) const;
		
		[[nodiscard]] float CrossProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2) const { return vec1.x * vec2.y - vec1.y * vec2.x; }
		[[nodiscard]] float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2) const { return vec1.x * vec2.x + vec1.y * vec2.y; }

		[[nodiscard]] sf::Vector2f CreateVector(const sf::Vector2f& fromPoint, const sf::Vector2f& tillPoint) const { return sf::Vector2f{ tillPoint.x - fromPoint.x, tillPoint.y - fromPoint.y }; }
	};
}

