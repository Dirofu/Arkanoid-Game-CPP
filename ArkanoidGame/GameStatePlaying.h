#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Snake.h"
#include "GameStateBase.h"

namespace ArkanoidGame
{
	class GameStatePlayingData : public GameStateBase
	{
	private:
		sf::Texture appleTexture;
		sf::Texture rockTexture;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		Snake snake;
		sf::Sprite apple;
		std::vector<sf::Sprite> rocks;
		int numEatenApples = 0;
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;

	public:
		void InitGameState() override;
		void ShutdownGameState() override;
		void HandleGameStateWindowEvent(const sf::Event& event) override;
		void UpdateGameState(float timeDelta) override;
		void DrawGameState(sf::RenderWindow& window) override;
	};
}
