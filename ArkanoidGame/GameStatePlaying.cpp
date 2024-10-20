#include "GameStatePlaying.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "Application.h"

namespace ArkanoidGame
{
	void GameStatePlayingData::InitGameState()
	{	
		LoadSnakeTextures(snake);
		assert(appleTexture.loadFromFile(TEXTURES_PATH + "Apple.png"));
		assert(rockTexture.loadFromFile(TEXTURES_PATH + "Rock.png"));
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		InitSnake(snake);

		InitSprite(apple, APPLE_SIZE, APPLE_SIZE, appleTexture);
		SetSpriteRandomPosition(apple, background.getGlobalBounds(), snake.body);

		rocks.resize(ROCKS_COUNT);
		for (sf::Sprite& rock : rocks) {
			InitSprite(rock, ROCK_SIZE, ROCK_SIZE, rockTexture);
			SetSpriteRandomPosition(rock, background.getGlobalBounds(), snake.body);
		}

		numEatenApples = 0;

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::ShutdownGameState()
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void GameStatePlayingData::HandleGameStateWindowEvent(const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				game.PushGameState(GameStateType::ExitDialog, false);
			}
		}
	}

	void GameStatePlayingData::UpdateGameState(float timeDelta)
	{
		Game& game = Application::Instance().GetGame();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			snake.direction = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			snake.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			snake.direction = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			snake.direction = SnakeDirection::Left;
		}

		MoveSnake(snake, timeDelta);

		if (CheckSpriteIntersection(*snake.head, apple)) {
			eatAppleSound.play();

			GrowSnake(snake);

			numEatenApples++;

			SetSpriteRandomPosition(apple, background.getGlobalBounds(), snake.body);

			if (game.CheckGameOption(GameOptions::WithAcceleration))
				snake.speed += ACCELERATION;
		}

		if (!game.CheckGameOption(GameOptions::InfiniteApples)
			|| !HasSnakeCollisionWithRect(snake, background.getGlobalBounds())
			|| CheckSnakeCollisionWithHimself(snake)
			|| FullCheckCollisions(rocks.begin(), rocks.end(), *snake.head))
		{
			gameOverSound.play();

			game.UpdateRecordTable(PLAYER_NAME, numEatenApples);
			game.PushGameState(GameStateType::GameOver, false);
		}

		scoreText.setString("Apples eaten: " + std::to_string(numEatenApples));
	}

	void GameStatePlayingData::DrawGameState(sf::RenderWindow& window)
	{
		window.draw(background);
		DrawSnake(snake, window);
		DrawSprite(apple, window);
		DrawSprites(rocks.begin(), rocks.end(), window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
