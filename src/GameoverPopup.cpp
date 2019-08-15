#include "pch.h"
#include "inc/GameoverPopup.h"

GameoverPopup::GameoverPopup() : 
	_gameoverWindow(sf::VideoMode(POPUP_WIDTH, POPUP_HEIGHT, 16), "Gameover")
{
	std::cout << "Constructed GameOver popup \n";
}

GameoverPopup::GameoverPopupResult GameoverPopup::Show()
{	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/GameOverPopupImg.png");
	sf::Sprite sprite(image);

	//Setup clickable regions

	//Play menu item coordinates
	GameoverPopupItem playButton;
	playButton.rect.top = POPUP_HEIGHT / 2;
	playButton.rect.height = POPUP_HEIGHT;
	playButton.rect.left = 0;
	playButton.rect.width = POPUP_WIDTH / 2;
	playButton.action = Retry;

	//Exit menu item coordinates
	GameoverPopupItem exitButton;
	exitButton.rect.top = POPUP_HEIGHT / 2;
	exitButton.rect.height = POPUP_HEIGHT;
	exitButton.rect.left = POPUP_WIDTH / 2;
	exitButton.rect.width = POPUP_WIDTH;
	exitButton.action = ExitGame;

	_popupItems.push_back(playButton);
	_popupItems.push_back(exitButton);

	_gameoverWindow.draw(sprite);
	_gameoverWindow.display();

	// get result part
	return GetPopupResponse();
}

GameoverPopup::GameoverPopupResult GameoverPopup::HandleClick(int x, int y)
{
	std::list<GameoverPopupItem>::iterator it;

	for (it = _popupItems.begin(); it != _popupItems.end(); it++)
	{
		sf::Rect<int> popupItemRect = (*it).rect;
		if (popupItemRect.height > y
			&& popupItemRect.top < y
			&& popupItemRect.left < x
			&& popupItemRect.width > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

GameoverPopup::GameoverPopupResult GameoverPopup::GetPopupResponse()
{
	sf::Event popupEvent;

	while (true)
	{
		while (_gameoverWindow.pollEvent(popupEvent))
		{
			if (popupEvent.type == sf::Event::Closed)
			{
				return ExitGame;
			}

			if (popupEvent.type == sf::Event::MouseButtonPressed)
			{
				GameoverPopupResult clickedResult = HandleClick(popupEvent.mouseButton.x, popupEvent.mouseButton.y);
				if (clickedResult != Nothing)
				{
					return clickedResult;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
