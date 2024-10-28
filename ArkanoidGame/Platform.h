#pragma once
#include "PlatformDirection.h"
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Platform
	{
	private:
		sf::Sprite platformSprite;
		PlatformDirection direction;
		float speed;

	public:
		PlatformDirection& GetDirection() { return direction; }
		sf::Sprite& GetSprite() { return platformSprite; }

		void SetDirection(PlatformDirection newDirection) { direction = newDirection; }
		float& GetSpeed() { return speed; }
		void SetSpeed(float newSpeed) { speed = newSpeed; }

		void InitializePlatform(sf::Texture& texture, float speed);
		void HandlePlayerInput();
		void MovePlatform(sf::FloatRect backgroundRect, float deltaTime);

		sf::Vector2f GetDirectionVector(PlatformDirection direction);

		bool HasCollisionWithRect(sf::Vector2f nextPosition, const sf::FloatRect& rect);

		void DrawPlatform(sf::RenderWindow& window);
	};
}