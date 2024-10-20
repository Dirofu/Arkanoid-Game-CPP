#include "GameStatePauseMenu.h"
#include "Game.h"
#include <assert.h>
#include "Application.h"

namespace ArkanoidGame
{
	void GameStatePauseMenuData::InitGameState()
	{
		MenuItem& rootItem = menu.GetRootItem();
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		titleText.setString("Pause");
		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setFillColor(sf::Color::Red);

		rootItem.SetChildrenOrientation(Orientation::Vertical);
		rootItem.SetChildrenAlignment(Alignment::Middle);
		rootItem.AddNewItemInChildren(resumeItem);
		rootItem.AddNewItemInChildren(exitItem);
		
		resumeItem.InitializeMenuItemText("Return to game", font, 24);
		exitItem.InitializeMenuItemText("Exit to main menu", font, 24);

		menu.InitMenuItem(rootItem);
		menu.SelectMenuItem(&resumeItem);
	}

	void GameStatePauseMenuData::ShutdownGameState()
	{
		// We dont need to free resources here, because they will be freed automatically
	}

	void GameStatePauseMenuData::HandleGameStateWindowEvent(const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				game.PopGameState();
			}

			if (menu.GetSelectedItem() == nullptr)
			{
				return;
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				if (menu.GetSelectedItem() == &resumeItem)
				{
					game.PopGameState();
				}
				else if (menu.GetSelectedItem() == &exitItem)
				{
					game.SwitchGameState(GameStateType::MainMenu);
				}
			}

			Orientation orientation = menu.GetSelectedItem()->GetMenuItemParent()->GetChildrenOrientation();
			if (event.key.code == sf::Keyboard::Up)
			{
				menu.SelectPreviousMenuItem();
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				menu.SelectNextMenuItem();
			}
		}
	}

	void GameStatePauseMenuData::UpdateGameState(float timeDelta)
	{

	}

	void GameStatePauseMenuData::DrawGameState(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		
		background.setSize(viewSize);
		window.draw(background);

		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.f }));
		titleText.setPosition(viewSize.x / 2.f, 100);
		window.draw(titleText);

		menu.DrawMenu(window, window.getView().getCenter(), { 0.5f, 0.f });
	}
}