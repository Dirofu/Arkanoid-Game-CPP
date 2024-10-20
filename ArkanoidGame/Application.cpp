#include "Application.h"
#include <cstdlib>

namespace ArkanoidGame
{
	Application::Application() :
		window(sf::VideoMode(ArkanoidGame::SCREEN_WIDTH, ArkanoidGame::SCREEN_HEGHT), ArkanoidGame::GAME_NAME)
	{
		// Init random number generator
		unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
		srand(seed);

		game.InitGame();
	}

	Application::~Application()
	{
		game.ShutdownGame();
	}

	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	void Application::Run()
	{
		// Init game clock
		sf::Clock gameClock;

		// Game loop
		while (window.isOpen()) {

			float startTime = gameClock.getElapsedTime().asSeconds();

			game.HandleWindowEvents(window);

			if (!window.isOpen()) {
				break;
			}

			if (game.UpdateGame(TIME_PER_FRAME))
			{
				window.clear();
				game.DrawGame(window);
				window.display();
			}
			else
			{
				window.close();
			}

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < TIME_PER_FRAME) {
				// Reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(TIME_PER_FRAME - deltaTime));
			}
		}
	}

}