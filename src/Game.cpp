#include "pch.h"
#include "inc/Game.h"
#include "inc/MainMenu.h"
#include "inc/SplashScreen.h"
#include "inc/GameoverPopup.h"
#include "inc/Utilities.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
	{
		return;
	}

	if (!LoadFonts()) 
	{
		LOG("Error while loading text fonts, returning.");
		return;
	}

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16), "Pong!");
	_mainWindow.setFramerateLimit(30); // limit frame rate
	
	_gameObjectManager.CreateGameObject<PlayerPaddle>("PlayerPaddle");
	_gameObjectManager.CreateGameObject<ComputerPaddle>("ComputerPaddle");
	_gameObjectManager.CreateGameObject<GameBall>("Ball");

	_gameObjectManager.SetGameObjectsDefaultPosition();

	_gameState = Game::ShowingSplash;

	// here is where the game flow logic and event handling is encapsulated
	while (!IsExiting())
	{
		GameLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	_mainWindow.close();
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent))
	{
		// if closing was requested then we exit from the game loop immediatly
		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Game::Exiting;
			return;
		}
	}

	switch (_gameState)
	{
		case Game::ShowingSplash:
			ShowSplashScreen();
			break;

		case Game::ShowingMenu:
			ShowMenu();
			break;

		case Game::Playing:
			_mainWindow.clear(sf::Color(0, 0, 0));

			_scoreBoard.Draw(_mainWindow); // draw scoreboard on main window

			GameMessage resultMessage = _gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);
			_mainWindow.display();
		
			if (resultMessage.IsError()) 
			{
				LOG("Error after game update: " << resultMessage.GetMessageString())
				// TODO 
				// DisplayErrorMessage();
			}
			else if (resultMessage.IsBallMiss()) 
			{
				LOG("Point scored: " << resultMessage.GetMessageString())
				_referee->InterpretBallMessage(resultMessage);
				result_t currentResult = _referee->GetCurrentResult();

				// TODO 
				// if referee get result is match done show end popup otherwise simply update scores
				_scoreBoard.UpdateScores(currentResult);
				_scoreBoard.Draw(_mainWindow);
				_mainWindow.display(); // display to update the score on the window

				// computer wins: gameover
				if (currentResult.computerScore == result_t::MAX_SCORE) 
				{
					ShowGameoverPopup();
				}
				// player wins!!
				else if (currentResult.playerScore == result_t::MAX_SCORE)
				{
					// TODO go to the next level?
				}
				// simply keep up with the match
				else 
				{
					// wait for one second and restart
					std::this_thread::sleep_for(std::chrono::seconds(1));
					// TODO countdown to restart
					_gameObjectManager.SetGameObjectsDefaultPosition();
					// TODO set a new randon angle for the ball
				}
			}

			break;
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
			_gameState = Game::Exiting;
			break;
		case MainMenu::Play:
			_gameState = Game::Playing;
			break;
		default:
			break;
	}
}

void Game::ShowGameoverPopup()
{
	GameoverPopup gameoverPopup;
	GameoverPopup::GameoverPopupResult result = gameoverPopup.Show();
	switch (result)
	{
		case GameoverPopup::ExitGame:
			_gameState = Game::Exiting;
			break;
		case GameoverPopup::Retry:
			// reset game objects position and restore playing window
			_gameObjectManager.SetGameObjectsDefaultPosition();
			_scoreBoard.Clear();
			_referee->ResetScore();
			_gameState = Game::Playing;
			break;
		default:
			break;
	}
}

// static members initialization
Game::GameState Game::_gameState = Uninitialized;
const std::string Game::Fonts::PATH_TO_FONTS = "C:/Users/Rebo/Documents/Fonts/";
sf::Font Game::Fonts::arialFont;
sf::RenderWindow Game::_mainWindow;
ScoreBoard Game::_scoreBoard;
GameObjectsManager Game::_gameObjectManager;
std::unique_ptr<Referee> Game::_referee = std::make_unique<Referee>();
