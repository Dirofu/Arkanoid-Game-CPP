#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameStateBase.h"

namespace ArkanoidGame
{
	class GameStateRecordsData : public GameStateBase
	{
	private:
		sf::Text titleText;
		std::vector<sf::Text> tableTexts;
		sf::Text hintText;

	public:
		void InitGameState() override;
		void ShutdownGameState() override;
		void HandleGameStateWindowEvent(const sf::Event& event) override;
		void UpdateGameState(float timeDelta) override;
		void DrawGameState(sf::RenderWindow& window) override;
	};
}