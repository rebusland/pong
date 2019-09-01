/**
 * TODO:
 *  - implement a warning popup to notify program errors
 *  - realize a more realistic computer paddle
 *  - provide difficulty level selection (tuning ball speed and computer paddle reactiveness)
 *	- command shortcut to momentarily pause the game
 *  - add a game options section allowing to select difficulty level, name, ball speed..
 *	- log4j as logging framework?
 *
 *	- Adapt comments format to fit Deoxygen standards (?)
 *	- Turn project into a CONAN project, if possible (?)
 *	- Measure time performance with chrono for each relevant method. Create a timer utility to be reused.
	  Is that possible to do tracing?
 *	- Unit testing (search for a valid framework) and test code coverage (GCOV on Windows is possible?)
 */

#pragma once
#include "ScoreBoard.h"
#include "Referee.h"
#include "PongObjectsManager.h"
#include "Ball.h"
#include "PlayerPaddle.h"
#include "ComputerPaddle.h"

 // path to default images for Sprite objects
// #define  BALL_DEFAULT_IMAGE_PATH "images/ball.png"
#define  BALL_DEFAULT_IMAGE_PATH "images/tennis-ball-icon-cropped.png"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetMainWindow() 
	{
		return _mainWindow;
	}

	/**
	 * True if font loading has been successful, false otherwise
	 */
	static bool LoadFonts() 
	{
		return Fonts::arialFont.loadFromFile(Fonts::PATH_TO_FONTS + "arial.ttf");
	}

	// pre-loaded fonts
	// TODO move in utility "package"
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

private:
	static bool IsExiting()
	{
		return _gameState == GameState::Exiting;
	}
	static void GameLoop();

	enum class GameState {
		Uninitialized, 
		ShowingSplash, 
		Paused,
		ShowingMenu, 
		Playing, 
		Exiting
	};

	static void ShowSplashScreen();
	static void ShowMenu();

	// TODO: NB each time this method is called a new gameover popup is created: ineffient; better to create the
	// popup once and then reuse it.
	static void ShowGameoverPopup();

	static GameState _gameState;

	static sf::RenderWindow _mainWindow;
	static ScoreBoard _scoreBoard;

	static PongObjectsManager _pongObjectsManager;
	static std::unique_ptr<Referee> _referee;
};
