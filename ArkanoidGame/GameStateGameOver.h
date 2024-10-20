#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateBase.h"

namespace ArkanoidGame
{
	class GameStateGameOverData : public GameStateBase
	{
	private:
		float timeSinceGameOver = 0.f;
		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;

	public:
		void InitGameState() override;
		void ShutdownGameState() override;
		void HandleGameStateWindowEvent(const sf::Event& event) override;
		void UpdateGameState(float timeDelta) override;
		void DrawGameState(sf::RenderWindow& window) override;
	};
}
