#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ArkanoidGame 
{
	class Application
	{
	public:
		Application(const Application& application) = delete;
		Application& operator=(const Application&) = delete;

		static Application& Instance();

		Game& GetGame()
		{ 
			return game; 
		}

		void Run();

	private:
		Application();
		~Application();
		Game game;
		sf::RenderWindow window;
	};

}


