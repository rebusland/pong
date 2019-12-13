#pragma once

#define MAIN_MENU_IMAGE_PATH "images/StartMenuImg.png"

class MainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play, Options };

	struct MenuItem
	{
		sf::Rect<int> rect;
		MenuResult action;
	};

	MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);

	static constexpr int MENU_HEIGHT = 460;
	static constexpr int MENU_WIDTH = 819;

	std::list<MenuItem> _menuItems;
};
