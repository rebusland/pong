#pragma once
#include "pch.h"

/*
 * Handles popup for game over message.
 * TODO structure is almost identical as MainMenu handler: check whether is possible to refactor popups/menu to centralize
 * logic and to avoid code duplication.
 */
class GameoverPopup 
{
public:
	enum GameoverPopupResult {Retry, ExitGame, Nothing};

	struct GameoverPopupItem
	{
	public:
		sf::Rect<int> rect;
		GameoverPopupResult action;
	};

	// constructor
	GameoverPopup();

	// display secondary window with popup
	GameoverPopupResult Show();
	void ClosePopup();

private:
	const GameoverPopupResult& GetGameoverPopupResult();
	GameoverPopupResult HandleClick(int x, int y);
	GameoverPopupResult GetPopupResponse();

	std::list<GameoverPopupItem> _popupItems;

	// secondary window object for the popup
	sf::RenderWindow _gameoverWindow;

	// popup sizes
	static constexpr int POPUP_WIDTH = 600;
	static constexpr int POPUP_HEIGHT = 340;
};
