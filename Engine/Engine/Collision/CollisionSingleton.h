#pragma once
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

	class CollisionSingleton final : public Singleton<CollisionSingleton>
	{
	public:
		void Reset();
		// bool ParseLevelSVG(const std::string& file, const int yAdjust);
		// bool ParseIntersectionsSVG(const std::string& file, const int yAdjust);
		
		void AddCollider(const Collider* object, const Rectf& collider);
		void RemoveCollider(const Collider* object);

		void UpdateCollider(const Collider* object, const Rectf& collider);

		[[no_discard]] std::vector<const Collider*> IsColliding(const Collider* object);
		[[no_discard]] bool IsCollidingWithWorld(const Rectf& shape) const;
		[[no_discard]] bool IsCollidingWithWorld(const sf::Vector2f& point1, const sf::Vector2f& point2) const;
		//temp
		[[no_discard]] std::vector<std::vector<sf::Vector2f>> GetLevelCollider() const { return m_LevelCollider; }

	private:
		std::map<const Collider*, Rectf> m_Colliders;
		std::vector<std::vector<sf::Vector2f>> m_LevelCollider;

		[[no_discard]] float Distance(const sf::Vector2f& a, const sf::Vector2f& b) const;
		[[no_discard]] float DistanceSquared(const sf::Vector2f& a, const sf::Vector2f& b) const;
		
		// taken from Prog2 Engine credits to Koen Samyn
		[[no_discard]] bool Raycast(const std::vector<sf::Vector2f>& vertices, const sf::Vector2f& rayP1, const sf::Vector2f& rayP2) const;
		[[no_discard]] bool Raycast(const sf::Vector2f* vertices, const size_t nrVertices, const sf::Vector2f& rayP1, const sf::Vector2f& rayP2) const;
		[[no_discard]] bool IntersectLineSegments(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& q1, const sf::Vector2f& q2, float& outLambda1, float& outLambda2, double epsilon = 1e-6) const;
		[[no_discard]] bool IsPointOnLineSegment(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b) const;
		[[no_discard]] bool AreRectsColliding(const Rectf& rect1, const Rectf& rect2) const;
		
		[[no_discard]] float CrossProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2) const { return vec1.x * vec2.y - vec1.y * vec2.x; }
		[[no_discard]] float DotProduct(const sf::Vector2f& vec1, const sf::Vector2f& vec2) const { return vec1.x * vec2.x + vec1.y * vec2.y; }

		[[no_discard]] sf::Vector2f CreateVector(const sf::Vector2f& fromPoint, const sf::Vector2f& tillPoint) const { return sf::Vector2f{ tillPoint.x - fromPoint.x, tillPoint.y - fromPoint.y }; }
	};
}

