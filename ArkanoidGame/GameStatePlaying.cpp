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
		assert(platformTexture.loadFromFile(TEXTURES_PATH + "Platform.png"));
		assert(ballTexture.loadFromFile(TEXTURES_PATH + "Ball.png"));
		assert(tileTexture.loadFromFile(TEXTURES_PATH + "Tile.png"));
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(bounceSoundBuffer.loadFromFile(SOUNDS_PATH + "Bounce.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		sound.SetBounceSound(bounceSoundBuffer);
		sound.SetGameOverSound(gameOverSoundBuffer);
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 0, 0));
		platform.InitializePlatform(platformTexture, INITIAL_PLATFORM_SPEED);
		ball.InitializeBall(ballTexture, INITIAL_BALL_SPEED);

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));
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

		platform.HandlePlayerInput();
		platform.MovePlatform(background.getGlobalBounds(), timeDelta);
		ball.MoveBall(timeDelta);

		if (ball.GetLeftBounds() < 0 || ball.GetRightBounds() > SCREEN_WIDTH)
		{
			ball.InvertHorizontalVelocity();
			sound.PlayBounceSound();
		}
		if (ball.GetTopBounds() < 0)
		{
			ball.InvertVerticalVelocity();
			sound.PlayBounceSound();
		}

		if (CheckSpriteCollision(platform.GetSprite(), ball.GetSprite()))
		{
			ball.InvertVerticalVelocity();
			sound.PlayBounceSound();
		}

		if (ball.GetBottomBounds() > SCREEN_HEGHT)
		{
			sound.PlayGameOverSound();
			game.UpdateRecordTable(PLAYER_NAME, score);
			game.PushGameState(GameStateType::GameOver, false);
		}
	}

	bool GameStatePlayingData::CheckSpriteCollision(const sf::Sprite& spriteFrom, const sf::Sprite& spriteTo)
	{
		sf::FloatRect boundsFrom = spriteFrom.getGlobalBounds();
		sf::FloatRect boundsTo = spriteTo.getGlobalBounds();
		return boundsFrom.intersects(boundsTo);
	}

	void GameStatePlayingData::DrawGameState(sf::RenderWindow& window)
	{
		window.draw(background);
		platform.DrawPlatform(window);
		ball.DrawBall(window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
