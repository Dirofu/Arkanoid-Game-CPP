#include "MenuItem.h"

namespace ArkanoidGame
{
	void MenuItem::InitializeMenuItemText(sf::String string, sf::Font& font, int size)
	{
		text.setString(string);
		text.setFont(font);
		text.setCharacterSize(size);
	}

	void MenuItem::InitializeMenuItemTextHint(sf::String string, sf::Font& font, int size, sf::Color color)
	{
		hintText.setString(string);
		hintText.setFont(font);
		hintText.setCharacterSize(size);
		hintText.setFillColor(color);
	}

	void MenuItem::UpdateText(sf::String string)
	{
		text.setString(string);
	}

	void MenuItem::SetTextColor(sf::Color color)
	{
		text.setFillColor(color);
	}

	void MenuItem::AddNewItemInChildren(MenuItem& item)
	{
		children.push_back(&item);
	}
}