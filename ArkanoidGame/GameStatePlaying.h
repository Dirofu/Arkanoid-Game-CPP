#pragma once
#include "Platform.h"
#include "GameStateBase.h"
#include "Ball.h"
#include "SoundManager.h"

namespace ArkanoidGame
{
	class GameStatePlayingData : public GameStateBase
	{
	private:
		sf::Texture platformTexture;
		sf::Texture ballTexture;
		sf::Texture tileTexture;
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;
		sf::SoundBuffer bounceSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		SoundManager sound;
		Platform platform;
		Ball ball;

		int score;

	public:
		void InitGameState() override;
		void ShutdownGameState() override;
		void HandleGameStateWindowEvent(const sf::Event& event) override;
		void UpdateGameState(float timeDelta) override;
		bool CheckSpriteCollision(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo);
		void DrawGameState(sf::RenderWindow& window) override;
	};
}
