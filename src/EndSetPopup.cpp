#include "pch.h"
#include "inc/EndSetPopup.h"
#include "inc/Utilities.h"

// static members definition
std::string EndSetPopup::SuccessPopupData::WINDOW_NAME = "Success";
std::string EndSetPopup::SuccessPopupData::IMG_PATH = "images/SuccessPopupImg.png";
std::string EndSetPopup::GameOverPopupData::WINDOW_NAME = "Game Over";
std::string EndSetPopup::GameOverPopupData::IMG_PATH = "images/GameOverPopupImg.png";

EndSetPopup::EndSetPopup(EndSetPopup::PopupType popupType) :
	_popupWindow(sf::VideoMode(POPUP_WIDTH, POPUP_HEIGHT, 16), "")
{
	LOG(__func__);
	switch (popupType)
	{
		case EndSetPopup::PopupType::Success:
			_popupWindow.setTitle(SuccessPopupData::WINDOW_NAME);
			_imgPath = SuccessPopupData::IMG_PATH;
			break;
		case EndSetPopup::PopupType::GameOver:
			_popupWindow.setTitle(GameOverPopupData::WINDOW_NAME);
			_imgPath = GameOverPopupData::IMG_PATH;
				break;
		default:
			LOG("Unsupported popup type");
			break;
	}
}

EndSetPopup::UserDecisionAfterEndSet EndSetPopup::Show()
{	//Load menu image from file
	sf::Texture image;
	image.loadFromFile(_imgPath);
	sf::Sprite sprite(image);

	//Setup clickable regions

	//Play menu item coordinates
	EndSetPopupItem playButton;
	playButton.rect.top = POPUP_HEIGHT / 2;
	playButton.rect.height = POPUP_HEIGHT;
	playButton.rect.left = 0;
	playButton.rect.width = POPUP_WIDTH / 2;
	playButton.action = Retry;

	//Exit menu item coordinates
	EndSetPopupItem exitButton;
	exitButton.rect.top = POPUP_HEIGHT / 2;
	exitButton.rect.height = POPUP_HEIGHT;
	exitButton.rect.left = POPUP_WIDTH / 2;
	exitButton.rect.width = POPUP_WIDTH;
	exitButton.action = ExitGame;

	_popupItems.push_back(playButton);
	_popupItems.push_back(exitButton);

	_popupWindow.draw(sprite);
	_popupWindow.display();

	// get result part
	return GetPopupResponse();
}

EndSetPopup::UserDecisionAfterEndSet EndSetPopup::HandleClick(int x, int y)
{
	std::list<EndSetPopupItem>::iterator it;

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

EndSetPopup::UserDecisionAfterEndSet EndSetPopup::GetPopupResponse()
{
	sf::Event popupEvent;

	while (true)
	{
		while (_popupWindow.pollEvent(popupEvent))
		{
			if (popupEvent.type == sf::Event::Closed)
			{
				return ExitGame;
			}

			if (popupEvent.type == sf::Event::MouseButtonPressed)
			{
				UserDecisionAfterEndSet clickedResult = HandleClick(popupEvent.mouseButton.x, popupEvent.mouseButton.y);
				if (clickedResult != Nothing)
				{
					return clickedResult;
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
