#pragma once
#include "SFML/Graphics.hpp"
#include "Text.h"
#include <list>
#include "MenuItem.h"

namespace ArkanoidGame
{
	class Menu
	{
	private:
		MenuItem rootItem;
		MenuItem* selectedItem = nullptr;

	public:
		MenuItem& GetRootItem() { return rootItem; }
		MenuItem* GetSelectedItem() { return selectedItem; }
	
	public:
		void InitMenuItem(MenuItem& menu);
		void SelectMenuItem(MenuItem* item);
		bool SelectPreviousMenuItem();
		bool SelectNextMenuItem();
		bool ExpandSelectedItem();
		bool CollapseSelectedItem();
		MenuItem* GetCurrentMenuContext();
		void DrawMenu(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin);
	};
}