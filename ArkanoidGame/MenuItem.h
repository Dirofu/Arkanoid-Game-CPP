#pragma once
#include <SFML/Graphics.hpp>
#include "Text.h"

namespace ArkanoidGame
{
	class MenuItem
	{
	private:
		sf::Text text;
		sf::Text hintText;
		Orientation childrenOrientation = Orientation::Vertical;
		Alignment childrenAlignment = Alignment::Min;
		float childrenSpacing = 0.f;
		sf::Color selectedColor = sf::Color::Yellow;
		sf::Color deselectedColor = sf::Color::White;
		bool isEnabled = true;
		MenuItem* parent = nullptr;
		std::vector<MenuItem*> children;

	public:
		sf::FloatRect GetFloatRect() { return text.getLocalBounds(); }

		Orientation GetChildrenOrientation() { return childrenOrientation; }
		Alignment GetChildrenAlignment() { return childrenAlignment; }
		float GetChildrenSpacing() { return childrenSpacing; }
		sf::Color GetColor(bool isSelect) { return isSelect ? selectedColor : deselectedColor; }
		bool GetEnableStatus() { return isEnabled; }
		std::vector<MenuItem*> GetMenuItemChildrens() { return children; }
		MenuItem* GetMenuItemParent() { return parent; }
		sf::Text& GetText() { return text; }
		sf::Text& GetHintText() { return hintText; }

		void SetParent(MenuItem* newParent) { parent = newParent; }
		void SetChildrenOrientation(Orientation orientation) { childrenOrientation = orientation; }
		void SetChildrenAlignment(Alignment alignment) { childrenAlignment = alignment; }
		void SetChildrenSpacing(float spacing) { childrenSpacing = spacing; }
		void SetColor(bool isSelect, sf::Color color) { isSelect ? selectedColor = color : deselectedColor = color; }
		void SetEnableStatus(bool status) { isEnabled = status; }

		void InitializeMenuItemText(sf::String text, sf::Font font, int size);
		void InitializeMenuItemTextHint(sf::String text, sf::Font font, int size, sf::Color color);
		void UpdateText(sf::String text);
		void SetTextColor(sf::Color color);
		void AddNewItemInChildren(MenuItem& item);
	};
}