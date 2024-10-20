#pragma once
#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "Sprite.h"
#include "GameSettings.h"
#include "GameStateBase.h"
#include <unordered_map>

namespace ArkanoidGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		ExitDialog,
		Records,
	};

	struct GameState
	{
		GameStateType type = GameStateType::None;
		GameStateBase* data = nullptr;
		bool isExclusivelyVisible = false;
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		GameOptions GetGameOptions() const { return options; }
		std::unordered_map<std::string, int> GetRecords() const { return recordsTable; }
		int GetRecords(std::string name) { return recordsTable[name]; }

	private:
		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;
		GameOptions options = GameOptions::Default;
		std::unordered_map<std::string, int> recordsTable;
	
	public:
		bool CheckGameOption(GameOptions option) const;
		void InitGame();
		void HandleWindowEvents(sf::RenderWindow& window);
		bool UpdateGame(float timeDelta); // Return false if game should be closed
		void DrawGame(sf::RenderWindow& window);
		void ShutdownGame();
		void PushGameState(GameStateType stateType, bool isExclusivelyVisible);
		void PopGameState();
		void SwitchGameState(GameStateType newState);
		void SetGameOptions(GameOptions option);
		void UpdateRecordTable(std::string name, int score);
		
	private:
		void InitGameState(GameState& state);
		void ShutdownGameState(GameState& state);
		void HandleWindowEventGameState(GameState& state, sf::Event& event);
		void UpdateGameState(GameState& state, float timeDelta);
		void DrawGameState(GameState& state, sf::RenderWindow& window);
	};
}
