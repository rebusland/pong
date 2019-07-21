#include "pch.h"
#include "Game.h"
#include "Paddle.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "GameoverPopup.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
	{
		return;
	}

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16), "Pang!");
	_mainWindow.setFramerateLimit(30); // limit frame rate

	PlayerPaddle *player1 = new PlayerPaddle();
	ComputerPaddle *computerPaddle = new ComputerPaddle();
	GameBall *ball = new GameBall();

	_gameObjectManager.Add("PaddlePlayer", player1);
	_gameObjectManager.Add("ComputerPaddle", computerPaddle);
	_gameObjectManager.Add("Ball", ball);

	SetGameObjectsDefaultPosition();

	_gameState = Game::ShowingSplash;

	// here is where the game flow logic and event handling is encapsulated
	while (!IsExiting())
	{
		GameLoop();
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	_mainWindow.close();
}

void Game::SetGameObjectsDefaultPosition() 
{
	// ball default position is at the center of the window
	_gameObjectManager.Get("Ball")->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - GameBall::BALL_WIDTH * 0.5);

	// player and computer paddle are at the centered and in opposite sides of the field
	_gameObjectManager.Get("PaddlePlayer") -> SetPosition((SCREEN_WIDTH / 2) - Paddle::PADDLE_WIDTH * 0.5, SCREEN_HEIGHT - PADDLE_VERTICAL_DISTANCE);
	_gameObjectManager.Get("ComputerPaddle") -> SetPosition((SCREEN_WIDTH / 2) - Paddle::PADDLE_WIDTH * 0.5, PADDLE_VERTICAL_DISTANCE);
}

bool Game::IsExiting()
{
	return _gameState == Game::Exiting;
}

sf::RenderWindow& Game::GetMainWindow()
{
	return _mainWindow;
}

std::vector<sf::FloatRect> Game::GetPaddlesBounds()
{
	return _gameObjectManager.GetPaddlesBounds();
}

sf::Vector2f Game::GetBallPosition()
{
	return _gameObjectManager.GetBallPosition();
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
	case Game::ShowingMenu:
		ShowMenu();
		break;

	case Game::ShowingSplash:
		ShowSplashScreen();
		break;

	case Game::Playing:
		_mainWindow.clear(sf::Color(0, 0, 0));

		GameMessage resultMessage = _gameObjectManager.UpdateAll();
		_gameObjectManager.DrawAll(_mainWindow);
		_mainWindow.display();
		
		if (resultMessage.IsError()) 
		{
			std::cout << "Error after game update: " << resultMessage.GetMessageString() << std::endl;
			// TODO 
			// DisplayErrorMessage();
		}
		else if (resultMessage.IsBallMiss()) 
		{
			std::cout << "Point scored: " << resultMessage.GetMessageString() << std::endl;
			_referee->InterpretBallMessage(resultMessage);
			
			// for the moment log current result
			_referee->GetCurrentResult();
			
			// TODO 
			// if referee get result is match done show end popup otherwise simply update scores

			ShowGameoverPopup();
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
		SetGameObjectsDefaultPosition();
		_gameState = Game::Playing;
		break;
	default:
		break;
	}
}

// static members initialized
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
std::unique_ptr<Referee> Game::_referee = std::make_unique<Referee>();
