#include "pch.h"
#include "inc/Game.h"
#include "inc/Utilities.h"
#include "inc/SplashScreen.h"
#include "inc/EndSetPopup.h"
#include "inc/MenuScreen.h"
#include "inc/OptionsScreen.h"

// static members initialization
Game::GameState Game::_gameState;
Game::DifficultyLevel Game::_difficultyLevel = Game::DifficultyLevel::Easy;
sf::RenderWindow Game::_mainWindow;
ScoreBoard Game::_scoreBoard;
sf::Text Game::_pausedGameTextBox;
PongObjectsManager Game::_pongObjectsManager;
std::unique_ptr<Referee> Game::_referee = std::make_unique<Referee>();

void Game::Start() 
{
	GameMessage setupInterfaceMsg = TrySetupGameInterface();

	if (setupInterfaceMsg.IsError())
	{
		LOG(setupInterfaceMsg.GetMessageString())
		// TODO DisplayErrorMessage()
		return;
	}
	_gameState = GameState::ShowingMenu;

	// create game objects in advance, they will survive for the whole game lifespan.
	_pongObjectsManager.CreateGameObjects();

	// setup all screens for later use
	MenuScreen menuScreen(_mainWindow, utils::for_sfml::fonts::arialFont);
	OptionsScreen optionsScreen(_mainWindow, utils::for_sfml::fonts::arialFont);

	// here is where the game flow logic and event handling is encapsulated
	while (_mainWindow.isOpen() && _gameState != GameState::Exiting)
	{
		// GameLoop();

		switch (_gameState)
		{
			case GameState::ShowingMenu: 
			{
				menuScreen.Open();
				break;
			}
			case GameState::ChangingSettings:
			{
				optionsScreen.Open();
				break;
			}
			case GameState::Playing:
			{
				Play();
				break;
			}
			case GameState::Paused:
			{
				PauseGame();
				break;
			}
			default: // EXITING
			{
				LOG("Exiting")
				break;
			}
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	_mainWindow.close();
}

GameMessage Game::TrySetupGameInterface()
{
	if (!utils::for_sfml::fonts::LoadFonts())
	{
		return GameMessage(GameMessage::ERROR, "Error while loading text fonts", true);
	}

	// setup paused game text box
	_pausedGameTextBox.setFont(utils::for_sfml::fonts::arialFont);
	_pausedGameTextBox.setFillColor(sf::Color::White);
	_pausedGameTextBox.setCharacterSize(70);
	_pausedGameTextBox.setStyle(sf::Text::Bold);
	_pausedGameTextBox.setString(PAUSED_GAME_STRING);

	_pausedGameTextBox.setPosition(
		sf::Vector2f(
			(Game::FIELD_WIDTH - _pausedGameTextBox.getLocalBounds().width) / 2,
			(Game::FIELD_HEIGHT - _pausedGameTextBox.getLocalBounds().height) / 2
		)
	);

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16), "Pong!");
	_mainWindow.setFramerateLimit(30); // limit frame rate

	SplashScreen splashScreen;
	return splashScreen.Show(_mainWindow);
}

void Game::PauseGame()
{
	sf::Event currentEvent;
	while (_mainWindow.pollEvent(currentEvent)) {
		if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = GameState::Exiting;
			return;
		} 
		else if (_gameState == GameState::Paused &&
			currentEvent.type == sf::Event::KeyPressed &&
			currentEvent.key.code == sf::Keyboard::Space)
		{
			LOG("Resume game")
			_gameState = GameState::Playing;
		}
	}

	_mainWindow.clear(sf::Color(0, 0, 0));

	// freeze on the window the last frame of the game
	_mainWindow.draw(_pausedGameTextBox);
	_scoreBoard.Draw(_mainWindow); // draw scoreboard on main window
	_pongObjectsManager.DrawAll(_mainWindow);

	_mainWindow.display();
}

void Game::ResetGame()
{
	_pongObjectsManager.SetGameObjectsDefaultPosition();
	_pongObjectsManager.GetBall()->SetupRandomStartingAngle();
	_scoreBoard.Clear();
	_referee->ResetScore();
	_gameState = GameState::Playing;
}

void Game::Play() 
{
	while (_mainWindow.isOpen() && _gameState == Game::GameState::Playing) {

		//
		// PROCESS INPUT EVENT
		//

		sf::Event currentEvent;
		while (_mainWindow.pollEvent(currentEvent))
		{
			// if closing was requested then we exit from the game loop immediatly
			if (currentEvent.type == sf::Event::Closed)
			{
				_gameState = GameState::Exiting;
				return;
			}

			// spacebar can be used to pause the game when playing
			if (_gameState == GameState::Playing &&
				currentEvent.type == sf::Event::KeyPressed &&
				currentEvent.key.code == sf::Keyboard::Space)
			{
				LOG("Game paused")
					_gameState = GameState::Paused;
				return;
			}
		}

		// 
		// UPDATE GAME
		// 

		_mainWindow.clear(sf::Color(0, 0, 0));

		// draw scoreboard on main window
		_scoreBoard.Draw(_mainWindow);

		GameMessage resultMessage = _pongObjectsManager.UpdateAll();
		_pongObjectsManager.DrawAll(_mainWindow);
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

			_scoreBoard.UpdateScores(currentResult);
			_scoreBoard.Draw(_mainWindow);

			// display to update the score on the window
			_mainWindow.display();

			// computer wins: gameover
			if (currentResult.computerScore == result_t::MAX_SCORE)
			{
				ShowEndSetPopup(EndSetPopup::PopupType::GameOver);
			}
			// player wins!!
			else if (currentResult.playerScore == result_t::MAX_SCORE)
			{
				ShowEndSetPopup(EndSetPopup::PopupType::Success);
				// TODO go then to the next level?
			}
			// simply keep up with the match
			else
			{
				// wait for one second and restart
				std::this_thread::sleep_for(std::chrono::seconds(1));
				// TODO countdown to restart
				_pongObjectsManager.SetGameObjectsDefaultPosition();

				if (resultMessage.GetMessageType() == GameMessage::COMPUTER_MISS)
				{
					// also, the ball random starting angle and direction is specified
					_pongObjectsManager.GetBall()->SetupRandomStartingAngle(GameBall::FieldSide::ComputerSide);
				}
				else if (resultMessage.GetMessageType() == GameMessage::PLAYER_MISS)
				{
					_pongObjectsManager.GetBall()->SetupRandomStartingAngle(GameBall::FieldSide::PlayerSide);
				}
			}
		}
		
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
}

void Game::ShowEndSetPopup(const EndSetPopup::PopupType& popupType)
{
	EndSetPopup endSetPopup(popupType);
	EndSetPopup::UserDecisionAfterEndSet result = endSetPopup.Show();
	switch (result)
	{
	case EndSetPopup::UserDecisionAfterEndSet::ExitGame:
		_gameState = GameState::Exiting;
		break;
	case EndSetPopup::UserDecisionAfterEndSet::Retry:
		ResetGame();
		break;
	default:
		break;
	}
}
