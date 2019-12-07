/**
 * TODO:
 *  - implement a warning popup to notify program errors
 *  - realize a more realistic computer paddle
 *  - provide difficulty level selection (tuning ball speed and computer paddle reactiveness)
 *	- if a player scores, at the next game the ball must be thrown in the oppont field (at random angle),
 *	  possibly at a lower speed until it reaches the paddle so that is more feasible for the opponent to
 *	  to hit the ball.
 *	- fix the annoying bug of ball occasionally bouncing back and forth when touching the paddle border.
 *	- write a general utility methods to center texts inside a box, for arbitrary lenght based on character size.
 *	  In fact, currently the player name inside the score box is centered by hard-coding values.
 *
 *	- log4j as logging framework?
 *	- Adapt comments format to fit Deoxygen standards (?)
 *	- Turn project into a CONAN project, if possible (?)
 *	- Measure time performance with chrono for each relevant method. Create a timer utility to be reused.
	  Is that possible to do tracing?
 *	- Unit testing (search for a valid framework) and test code coverage (GCOV on Windows is possible?)
 */

#pragma once
#include "ScoreBoard.h"
#include "EndSetPopup.h"
#include "Referee.h"
#include "PongObjectsManager.h"
#include "Ball.h"
#include "PlayerPaddle.h"
#include "ComputerPaddle.h"

#define PAUSED_GAME_STRING "GAME PAUSED"
#define BALL_DEFAULT_IMAGE_PATH "images/tennis-ball-icon-cropped.png"
#define DEF_COMPUTER_NAME "HAL"

// TODO let the user choose its gaming name
#define DEF_PLAYER_NAME "USER"


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

	enum class DifficultyLevel {
		Easy,
		Medium,
		Hard,
		Impossible
	};

private:
	enum class GameState {
		Paused,
		ShowingMenu,
		Playing,
		Exiting
	};

	static void GameLoop();

	static GameMessage TrySetupGameInterface();

	/**
	 * Temporarily pause the game: freeze the window
	 */
	static void PauseGame();
	static void ShowMenu();

	/**
	 * Displays the popup as the set is over. This can be either a win or gameover screen,
	 * depending on the provided PopupType
	 */
	static void ShowEndSetPopup(const EndSetPopup::PopupType&);

	static void SetDifficutlyLevel(const DifficultyLevel& diffLevel)
	{
		_difficultyLevel = diffLevel;
	}

	static DifficultyLevel GetDifficultyLevel()
	{
		return _difficultyLevel;
	}

	// reset game objects position and scores, setting the game state to "Playing"
	static void ResetGame();

	static GameState _gameState;
	static DifficultyLevel _difficultyLevel;

	static sf::RenderWindow _mainWindow;
	static ScoreBoard _scoreBoard;

	static sf::Text _pausedGameTextBox;

	static PongObjectsManager _pongObjectsManager;
	static std::unique_ptr<Referee> _referee;
};
