#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateBase.h"

namespace ArkanoidGame
{
	class GameStateMainMenuData : public GameStateBase
	{
	private:
		MenuItem startGameItem;
		MenuItem optionsItem;
		MenuItem optionsInfiniteApplesItem;
		MenuItem optionsWithAccelerationItem;
		MenuItem recordsItem;
		MenuItem exitGameItem;
		MenuItem yesItem;
		MenuItem noItem;

	public:
		void InitGameState() override;
		void ShutdownGameState() override;
		void HandleGameStateWindowEvent(const sf::Event& event) override;
		void UpdateGameState(float timeDelta) override;
		void DrawGameState(sf::RenderWindow& window) override;
	};
}