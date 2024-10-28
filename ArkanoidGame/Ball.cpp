#include "Ball.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	void Ball::InitializeBall(sf::Texture& texture, float newSpeed)
	{
		float angle = 45.0f * 3.14f / 180.0f;
		float heightPosition = SCREEN_HEGHT - BALL_SIZE * 3.f;
		speed = newSpeed;

		ballSprite.setTexture(texture);
		ballSprite.setPosition(SCREEN_WIDTH / 2, heightPosition);
		SetSpriteRelativeOrigin(ballSprite, .5f, .5f);
		SetSpriteSize(ballSprite, BALL_SIZE, BALL_SIZE);

		velocity = {
			speed * std::cos(angle),
			speed * std::sin(-angle)};
	}

	void Ball::MoveBall(float deltaTime)
	{
		ballSprite.move(velocity * deltaTime);
	}

	void Ball::InvertHorizontalVelocity()
	{
		velocity.x = -velocity.x;
	}

	void Ball::InvertVerticalVelocity()
	{
		velocity.y = -velocity.y;
	}

	void Ball::DrawBall(sf::RenderWindow& window)
	{
		window.draw(ballSprite);
	}
}