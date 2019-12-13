#include "pch.h"
#include "inc/MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile(MAIN_MENU_IMAGE_PATH);
	sf::Sprite sprite(image);

	//Setup clickable regions

	const int selectionButtonWidth = (int) (MENU_HEIGHT / 3);

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.left = 0;
	playButton.rect.width = MENU_WIDTH;
	playButton.rect.top = 0;
	playButton.rect.height = selectionButtonWidth;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = MENU_WIDTH;
	exitButton.rect.top = selectionButtonWidth;
	exitButton.rect.height = selectionButtonWidth * 2;
	exitButton.action = Exit;

	// Options menu item coordinates
	MenuItem optionsButton;
	optionsButton.rect.left = 0;
	optionsButton.rect.width = MENU_WIDTH;
	optionsButton.rect.top = selectionButtonWidth * 2;
	optionsButton.rect.height = selectionButtonWidth * 3;
	optionsButton.action = Options;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);
	_menuItems.push_back(optionsButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
