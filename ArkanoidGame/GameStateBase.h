#pragma once
#include "MenuItem.h"
#include "Menu.h"

namespace ArkanoidGame
{
	class GameStateBase
	{
	protected:
		sf::Font font;
		Menu menu;

	public:
		virtual void InitGameState() {};
		virtual void ShutdownGameState() {};
		virtual void HandleGameStateWindowEvent(const sf::Event& event) {};
		virtual void UpdateGameState(float timeDelta) {};
		virtual void DrawGameState(sf::RenderWindow& window) {};
	};
}