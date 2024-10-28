#include "Menu.h"
#include <assert.h>

namespace ArkanoidGame
{
	void Menu::InitMenuItem(MenuItem& item)
	{
		for (auto& child : item.GetMenuItemChildrens())
		{
			child->SetParent(&item);
			InitMenuItem(*child);
		}
	}

	void Menu::SelectMenuItem(MenuItem* item)
	{
		assert(item != &rootItem);

		if (selectedItem == item)
			return;

		if (item && !item->GetEnableStatus())
			return;

		if (selectedItem)
			selectedItem->SetTextColor(selectedItem->GetColor(false));

		selectedItem = item;

		if (selectedItem)
			selectedItem->SetTextColor(selectedItem->GetColor(true));
	}

	bool Menu::SelectPreviousMenuItem()
	{
		if (selectedItem)
		{
			MenuItem* parent = selectedItem->GetMenuItemParent();
			assert(parent);
			std::vector<MenuItem*> childrens = parent->GetMenuItemChildrens();
			auto it = std::find(childrens.begin(), childrens.end(), selectedItem);

			if (it != childrens.begin())
			{
				SelectMenuItem(*(--it));
				return true;
			}
		}
		return false;
	}

	bool Menu::SelectNextMenuItem()
	{
		if (selectedItem)
		{
			MenuItem* parent = selectedItem->GetMenuItemParent();
			assert(parent); // There always should be parent
			std::vector<MenuItem*> childrens = parent->GetMenuItemChildrens();
			auto it = std::find(childrens.begin(), childrens.end(), selectedItem);

			if (it != childrens.end() - 1)
			{
				SelectMenuItem(*(++it));
				return true;
			}
		}
		return false;
	}

	bool Menu::ExpandSelectedItem()
	{
		if (selectedItem && selectedItem->GetMenuItemChildrens().size() > 0)
		{
			SelectMenuItem(selectedItem->GetMenuItemChildrens().front());
			return true;
		}

		return false;
	}

	bool Menu::CollapseSelectedItem()
	{
		if (selectedItem && selectedItem->GetMenuItemParent() && selectedItem->GetMenuItemParent() != &rootItem)
		{
			SelectMenuItem(selectedItem->GetMenuItemParent());
			return true;
		}
		return false;
	}

	MenuItem* Menu::GetCurrentMenuContext()
	{
		return selectedItem ? selectedItem->GetMenuItemParent() : &rootItem;
	}

	void Menu::DrawMenu(sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f origin)
	{
		MenuItem* expandedItem = GetCurrentMenuContext();

		std::vector<sf::Text*> texts;
		texts.reserve(expandedItem->GetMenuItemChildrens().size());

		for (MenuItem* child : expandedItem->GetMenuItemChildrens())
		{
			if (child->GetEnableStatus())
			{
				texts.push_back(&child->GetText());
			}
		}

		DrawTextList(
			window, 
			texts, 
			expandedItem->GetChildrenSpacing(), 
			expandedItem->GetChildrenOrientation(), 
			expandedItem->GetChildrenAlignment(),
			position, 
			origin);
	}
}
