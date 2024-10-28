#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStateBase.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "Application.h"

namespace ArkanoidGame
{
	bool Game::CheckGameOption(GameOptions option) const
	{
		return (std::uint8_t)options & (std::uint8_t)option;
	}

	void Game::InitGame()
	{
		recordsTable =
		{
			{"John", MAX_TILES * POINTS_PER_TILE / 2},
			{"Jane", MAX_TILES * POINTS_PER_TILE / 3 },
			{"Alice", MAX_TILES * POINTS_PER_TILE / 4 },
			{"Bob", MAX_TILES * POINTS_PER_TILE / 5 },
			{"Clementine", MAX_TILES * POINTS_PER_TILE / 5 },
		};

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchGameState(GameStateType::MainMenu);
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			
			if (gameStateStack.size() > 0)
			{
				HandleWindowEventGameState(gameStateStack.back(), event);
			}
		}
	}

	bool Game::UpdateGame(float timeDelta)
	{
		if (gameStateChangeType == GameStateChangeType::Switch)
		{
			while (gameStateStack.size() > 0)
			{
				ShutdownGameState(gameStateStack.back());
				gameStateStack.pop_back();
			}
		}
		else if (gameStateChangeType == GameStateChangeType::Pop)
		{
			if (gameStateStack.size() > 0)
			{
				ShutdownGameState(gameStateStack.back());
				gameStateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			gameStateStack.push_back({ pendingGameStateType, nullptr, pendingGameStateIsExclusivelyVisible });
			InitGameState(gameStateStack.back());
		}

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (gameStateStack.size() > 0)
		{
			UpdateGameState(gameStateStack.back(), timeDelta);
			return true;
		}

		return false;
	}

	void Game::DrawGame(sf::RenderWindow& window)
	{
		if (gameStateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = gameStateStack.rbegin(); it != gameStateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->isExclusivelyVisible)
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				DrawGameState(**it, window);
			}
		}
	}

	void Game::ShutdownGame()
	{
		while (gameStateStack.size() > 0)
		{
			ShutdownGameState(gameStateStack.back());
			gameStateStack.pop_back();
		}

		gameStateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushGameState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		gameStateChangeType = GameStateChangeType::Push;
	}

	void Game::PopGameState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchGameState(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		gameStateChangeType = GameStateChangeType::Switch;
	}

	void Game::SetGameOptions(GameOptions options)
	{
		this->options = options;
	}

	void Game::UpdateRecordTable(std::string name, int score)
	{
		recordsTable[name] = std::max(recordsTable[name], score);
	}

	void Game::InitGameState(GameState& state)
	{
		Game& game = Application::Instance().GetGame();

		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			state.data = new GameStateMainMenuData();
			(*(GameStateMainMenuData*)state.data).InitGameState();
			break;
		}
		case GameStateType::Playing:
		{
			state.data = new GameStatePlayingData();
			(*(GameStatePlayingData*)state.data).InitGameState();
			break;
		}
		case GameStateType::GameOver:
		{
			state.data = new GameStateGameOverData();
			(*(GameStateGameOverData*)state.data).InitGameState();
			break;
		}
		case GameStateType::ExitDialog:
		{
			state.data = new GameStatePauseMenuData();
			(*(GameStatePauseMenuData*)state.data).InitGameState();
			break;
		}
		case GameStateType::Records:
		{
			state.data = new GameStateRecordsData();
			(*(GameStateRecordsData*)state.data).InitGameState();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void Game::ShutdownGameState(GameState& state)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			(*(GameStateMainMenuData*)state.data).ShutdownGameState();
			delete (GameStateMainMenuData*)state.data;
			break;
		}
		case GameStateType::Playing:
		{
			(*(GameStatePlayingData*)state.data).ShutdownGameState();
			delete (GameStatePlayingData*)state.data;
			break;
		}
		case GameStateType::GameOver:
		{
			(*(GameStateGameOverData*)state.data).ShutdownGameState();
			delete (GameStateGameOverData*)state.data;
			break;
		}
		case GameStateType::ExitDialog:
		{
			(*(GameStatePauseMenuData*)state.data).ShutdownGameState();
			delete (GameStatePauseMenuData*)state.data;
			break;
		}
		case GameStateType::Records:
		{
			(*(GameStateRecordsData*)state.data).ShutdownGameState();
			delete (GameStateRecordsData*)state.data;
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}

		state.data = nullptr;
	}

	void Game::HandleWindowEventGameState(GameState& state, sf::Event& event)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			(*(GameStateMainMenuData*)state.data).HandleGameStateWindowEvent(event);
			break;
		}
		case GameStateType::Playing:
		{
			(*(GameStatePlayingData*)state.data).HandleGameStateWindowEvent(event);
			break;
		}
		case GameStateType::GameOver:
		{
			(*(GameStateGameOverData*)state.data).HandleGameStateWindowEvent(event);
			break;
		}
		case GameStateType::ExitDialog:
		{
			(*(GameStatePauseMenuData*)state.data).HandleGameStateWindowEvent(event);
			break;
		}
		case GameStateType::Records:
		{
			(*(GameStateRecordsData*)state.data).HandleGameStateWindowEvent(event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void Game::UpdateGameState(GameState& state, float timeDelta)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			(*(GameStateMainMenuData*)state.data).UpdateGameState(timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			(*(GameStatePlayingData*)state.data).UpdateGameState(timeDelta);
			break;
		}
		case GameStateType::GameOver:
		{
			(*(GameStateGameOverData*)state.data).UpdateGameState(timeDelta);
			break;
		}
		case GameStateType::ExitDialog:
		{
			(*(GameStatePauseMenuData*)state.data).UpdateGameState(timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			(*(GameStateRecordsData*)state.data).UpdateGameState(timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void Game::DrawGameState(GameState& state, sf::RenderWindow& window)
	{
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			(*(GameStateMainMenuData*)state.data).DrawGameState(window);
			break;
		}
		case GameStateType::Playing:
		{
			(*(GameStatePlayingData*)state.data).DrawGameState(window);
			break;
		}
		case GameStateType::GameOver:
		{
			(*(GameStateGameOverData*)state.data).DrawGameState(window);
			break;
		}
		case GameStateType::ExitDialog:
		{
			(*(GameStatePauseMenuData*)state.data).DrawGameState(window);
			break;
		}
		case GameStateType::Records:
		{
			(*(GameStateRecordsData*)state.data).DrawGameState(window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
}
