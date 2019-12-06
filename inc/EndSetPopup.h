#pragma once

/*
 * Handles popup appearing when the set comes to an end. It can be a game over :( or a success :) message.
 */
class EndSetPopup
{
public:
	enum UserDecisionAfterEndSet { Retry, ExitGame, Nothing };

	enum class PopupType { GameOver, Success };

	static struct SuccessPopupData
	{
		static std::string WINDOW_NAME;
		static std::string IMG_PATH;
	};

	static struct GameOverPopupData 
	{
		static std::string WINDOW_NAME;
		static std::string IMG_PATH;
	};

	struct EndSetPopupItem
	{
	public:
		sf::Rect<int> rect;
		UserDecisionAfterEndSet action;
	};

	/**
	 * Which screen to load (success or gameover) is passed via constructor
	 */
	EndSetPopup(EndSetPopup::PopupType);

	// display secondary window with popup
	UserDecisionAfterEndSet Show();
	void ClosePopup();

private:
	UserDecisionAfterEndSet HandleClick(int x, int y);
	UserDecisionAfterEndSet GetPopupResponse();

	std::list<EndSetPopupItem> _popupItems;

	// secondary window object for the popup
	sf::RenderWindow _popupWindow;

	std::string _imgPath;

	// popup sizes
	static constexpr int POPUP_WIDTH = 600;
	static constexpr int POPUP_HEIGHT = 340;
};

