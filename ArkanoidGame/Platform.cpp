#include "Platform.h"
#include "GameSettings.h"
#include "Sprite.h"

namespace ArkanoidGame
{
	void Platform::InitializePlatform(sf::Texture& texture, float speed)
	{
		float heightPosition = SCREEN_HEGHT - PLATFORM_SIZE;

		platformSprite.setTexture(texture);
		platformSprite.setColor(sf::Color(41, 255, 255));
		platformSprite.setPosition(SCREEN_WIDTH / 2, heightPosition);
		SetSpriteSize(platformSprite, PLATFORM_SIZE * 3.f, PLATFORM_SIZE / 2.f);
		this->speed = speed;
	}

	void Platform::HandlePlayerInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			direction = PlatformDirection::Left;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction = PlatformDirection::Right;
		else
			direction = PlatformDirection::None;
	}

	void Platform::MovePlatform(sf::FloatRect backgroundRect, float deltaTime)
	{
		float shift = speed * deltaTime;
		const sf::Vector2f direction = GetDirectionVector(this->direction) * shift / PLATFORM_SIZE;
		sf::Vector2f nextPoint = platformSprite.getPosition() + direction;

		if (HasCollisionWithRect(nextPoint, backgroundRect))
		{
			platformSprite.setPosition(nextPoint);
		}
	}

	sf::Vector2f Platform::GetDirectionVector(PlatformDirection direction)
	{
		sf::Vector2f result;

		switch (direction)
		{
			case PlatformDirection::Right:
			{
				result = { PLATFORM_SIZE, 0.f };
				break;
			}
			case PlatformDirection::Left:
			{
				result = { -PLATFORM_SIZE, 0.f };
				break;
			}
			case PlatformDirection::None:
			{
				result = { 0.f, 0.f };
				break;
			}
		}

		return result;
	}

	bool Platform::HasCollisionWithRect(sf::Vector2f nextPosition, const sf::FloatRect& rect)
	{
		if (direction == PlatformDirection::Right)
			nextPosition.x += PLATFORM_SIZE * 3.f;
		else
			nextPosition.x += PLATFORM_SIZE / 3.f;

		bool result = rect.contains(nextPosition);
		return result;
	}

	void Platform::DrawPlatform(sf::RenderWindow& window)
	{
		window.draw(platformSprite);
	}
}