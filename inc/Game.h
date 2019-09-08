/**
 * TODO:
 *  - implement a warning popup to notify program errors
 *  - realize a more realistic computer paddle
 *  - provide difficulty level selection (tuning ball speed and computer paddle reactiveness)
 *	- command shortcut to momentarily pause the game
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

#define PAUSED_GAME_STRING "GAME PAUSED"
#define BALL_DEFAULT_IMAGE_PATH "images/tennis-ball-icon-cropped.png"

class Game
{

public:
	static void Start();
	static sf::RenderWindow& GetMainWindow() 
	{
		return _mainWindow;
	}

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
	enum class GameState {
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	static bool IsExiting()
	{
		return _gameState == GameState::Exiting;
	}
	static void GameLoop();

	static GameMessage TrySetupGameInterface();

	/**
	 * Temporarily pause the game: freeze the window
	 */
	static void PauseGame();
	static void ShowMenu();

	// TODO: NB each time this method is called a new gameover popup is created: ineffient;
	// better to create the popup once and then reuse it.
	static void ShowGameoverPopup();

	// reset game objects position and scores, setting the game state to "Playing"
	static void ResetGame();

	static GameState _gameState;

	static sf::RenderWindow _mainWindow;
	static ScoreBoard _scoreBoard;

	static sf::Text _pausedGameTextBox;

	static PongObjectsManager _pongObjectsManager;
	static std::unique_ptr<Referee> _referee;
};
