/**
 * TODO:
 *  - implement a warning popup to notify program errors
 *  - replace ball and paddles images with a sfml Shape objects
 *  - realize a more realistic computer paddle
 *  - provide difficulty level selection (tuning ball speed and computer paddle reactiveness)
 */

#pragma once
#include "ScoreBoard.h"
#include "Referee.h"
#include "PlayerPaddle.h"
#include "ComputerPaddle.h"
#include "Ball.h"
#include "GameObjectManager.h"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetMainWindow();
	// static sf::RenderWindow& GetGameoverWindow();
	static std::vector<sf::FloatRect> GetPaddlesBounds();
	static sf::Vector2f GetBallPosition();

	/**
	 * True if font loading has been successful, false otherwise
	 */
	static bool LoadFonts();

	// pre-loaded fonts
	static struct Fonts {
		static sf::Font arialFont;

		static const std::string PATH_TO_FONTS;
	};

	// window size
	static constexpr int SCREEN_WIDTH = 800;
	static constexpr int SCREEN_HEIGHT = 480;

	// score board side bar sizes
	static constexpr int SCORE_BOARD_WIDTH = 100;
	static constexpr int SCORE_BOARD_HEIGHT = SCREEN_HEIGHT;

	// score boxes (in the bar) sizes
	static constexpr int SCORE_BOX_WIDTH = SCORE_BOARD_WIDTH;
	static constexpr int SCORE_BOX_HEIGHT = 50;

	// play field size
	static constexpr int FIELD_WIDTH = SCREEN_WIDTH - SCORE_BOARD_WIDTH;
	static constexpr int FIELD_HEIGHT = SCREEN_HEIGHT;

	// update time for the window (according to an avarage 30 fps)
	static constexpr float WIN_UPDATE_TIME = (float)1 / 30;

	static constexpr int PADDLE_VERTICAL_DISTANCE = 60;

private:
	static void SetGameObjectsDefaultPosition();
	static bool IsExiting();
	static void GameLoop();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing, Exiting
	};

	static void ShowSplashScreen();
	static void ShowMenu();

	// TODO: NB each time this method is called a new gameover popup is created: ineffient; better to create the
	// popup once and then reuse it.
	static void ShowGameoverPopup();

	static GameState _gameState;

	static sf::RenderWindow _mainWindow;
	// static sf::RenderWindow _gameoverWindow;
	static ScoreBoard _scoreBoard;

	static GameObjectManager _gameObjectManager;
	static std::unique_ptr<Referee> _referee;
};
