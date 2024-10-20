#pragma once
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameStateBase.h"

namespace ArkanoidGame
{
	class GameStatePauseMenuData : public GameStateBase
	{
	private:
		sf::RectangleShape background;
		sf::Text titleText;
		MenuItem resumeItem;
		MenuItem exitItem;

	public:
		void InitGameState() override;
		void ShutdownGameState() override;
		void HandleGameStateWindowEvent(const sf::Event& event) override;
		void UpdateGameState(float timeDelta) override;
		void DrawGameState(sf::RenderWindow& window) override;
	};
}
