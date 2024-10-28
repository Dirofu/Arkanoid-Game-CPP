#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>
#include "Application.h"

namespace ArkanoidGame
{
	void GameStateMainMenuData::InitGameState()
	{
		MenuItem& rootItem = menu.GetRootItem();
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		rootItem.GetHintText().setString(GAME_NAME);
		rootItem.GetHintText().setFont(font);
		rootItem.GetHintText().setCharacterSize(48);
		rootItem.GetHintText().setFillColor(sf::Color::Red);
		rootItem.SetChildrenOrientation(Orientation::Vertical);
		rootItem.SetChildrenAlignment(Alignment::Middle);
		rootItem.SetChildrenSpacing(10.f);
		rootItem.AddNewItemInChildren(startGameItem);
		rootItem.AddNewItemInChildren(optionsItem);
		rootItem.AddNewItemInChildren(recordsItem);
		rootItem.AddNewItemInChildren(exitGameItem);

		startGameItem.InitializeMenuItemText("Start Game", font, 24);

		optionsItem.InitializeMenuItemText("Options", font, 24);
		optionsItem.InitializeMenuItemTextHint("Options", font, 48, sf::Color::Red);
		optionsItem.SetChildrenOrientation(Orientation::Vertical);
		optionsItem.SetChildrenAlignment(Alignment::Middle);
		optionsItem.SetChildrenSpacing(10.f);
		optionsItem.AddNewItemInChildren(optionsInfiniteApplesItem);
		optionsItem.AddNewItemInChildren(optionsWithAccelerationItem);

		optionsInfiniteApplesItem.InitializeMenuItemText("Infinite Apples: On/Off", font, 24);
		optionsWithAccelerationItem.InitializeMenuItemText("With Acceleration: On/Off", font, 24);
		
		recordsItem.InitializeMenuItemText("Records", font, 24);
		
		exitGameItem.InitializeMenuItemText("Exit Game", font, 24);
		exitGameItem.InitializeMenuItemTextHint("Are you sure?", font, 24, sf::Color::Red);
		exitGameItem.SetChildrenOrientation(Orientation::Horizontal);
		exitGameItem.SetChildrenAlignment(Alignment::Middle);
		exitGameItem.SetChildrenSpacing(10.f);
		exitGameItem.AddNewItemInChildren(yesItem);
		exitGameItem.AddNewItemInChildren(noItem);

		yesItem.InitializeMenuItemText("Yes", font, 24);
		noItem.InitializeMenuItemText("No", font, 24);
		
		menu.InitMenuItem(rootItem);
		menu.SelectMenuItem(&startGameItem);
	}

	void GameStateMainMenuData::ShutdownGameState()
	{
		// No need to do anything here
	}

	void GameStateMainMenuData::HandleGameStateWindowEvent(const sf::Event& event)
	{
		Game& game = Application::Instance().GetGame();

		if (!menu.GetSelectedItem())
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				menu.CollapseSelectedItem();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (menu.GetSelectedItem() == &startGameItem)
				{
					game.SwitchGameState(GameStateType::Playing);
				}
				else if (menu.GetSelectedItem() == &optionsItem)
				{
					menu.ExpandSelectedItem();
				}
				else if (menu.GetSelectedItem() == &optionsInfiniteApplesItem)
				{
					game.SetGameOptions((GameOptions)((std::uint8_t)game.GetGameOptions() ^ (std::uint8_t)GameOptions::InfiniteApples));
				}
				else if (menu.GetSelectedItem() == &optionsWithAccelerationItem)
				{
					game.SetGameOptions((GameOptions)((std::uint8_t)game.GetGameOptions() ^ (std::uint8_t)GameOptions::WithAcceleration));
				}
				else if (menu.GetSelectedItem() == &recordsItem)
				{
					game.PushGameState(GameStateType::Records, true);
				}
				else if (menu.GetSelectedItem() == &exitGameItem)
				{
					menu.ExpandSelectedItem();
				}
				else if (menu.GetSelectedItem() == &yesItem)
				{
					game.SwitchGameState(GameStateType::None);
				}
				else if (menu.GetSelectedItem() == &noItem)
				{
					menu.CollapseSelectedItem();
				}
				else
				{
					menu.ExpandSelectedItem();
				}
			}
			
			Orientation orientation = menu.GetSelectedItem()->GetMenuItemParent()->GetChildrenOrientation();
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SelectPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
						orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SelectNextMenuItem();
			}
		}
	}

	void GameStateMainMenuData::UpdateGameState(float timeDelta)
	{
		Game& game = Application::Instance().GetGame();

		bool isInfiniteApples = ((std::uint8_t)game.GetGameOptions()  & (std::uint8_t)GameOptions::InfiniteApples) != (std::uint8_t)GameOptions::Empty;
		optionsInfiniteApplesItem.UpdateText("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));

		bool isWithAcceleration = ((std::uint8_t)game.GetGameOptions() & (std::uint8_t)GameOptions::WithAcceleration) != (std::uint8_t)GameOptions::Empty;
		optionsWithAccelerationItem.UpdateText("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
	}

	void GameStateMainMenuData::DrawGameState(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &menu.GetCurrentMenuContext()->GetHintText();
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		menu.DrawMenu(window, viewSize / 2.f, { 0.5f, 0.f });
	}
}