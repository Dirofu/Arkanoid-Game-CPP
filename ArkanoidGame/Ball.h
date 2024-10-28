#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameSettings.h"
#include "Vector.h"
#include <cmath>

namespace ArkanoidGame
{
	class Ball 
	{
	private:
		sf::Sprite ballSprite;
		sf::Vector2f velocity;
		float speed;

	public:
		float GetLeftBounds() { return ballSprite.getPosition().x - BALL_SIZE; }
		float GetRightBounds() { return ballSprite.getPosition().x + BALL_SIZE; }
		float GetTopBounds() { return ballSprite.getPosition().y - BALL_SIZE; }
		float GetBottomBounds() { return ballSprite.getPosition().y + BALL_SIZE; }
		sf::Sprite& GetSprite() { return ballSprite; }
		sf::Vector2f& GetVelocity() { return velocity; }
		void InitializeBall(sf::Texture& texture, float newSpeed);
		void MoveBall(float deltaTime);
		void InvertHorizontalVelocity();
		void InvertVerticalVelocity();
		void DrawBall(sf::RenderWindow& window);
	};
}